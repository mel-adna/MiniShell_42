/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:58:56 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/13 21:55:40 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_addstr(char ***arr, char *new_str)
{
	int		i;
	char	**new_arr;

	i = 0;
	if (*arr == NULL)
	{
		new_arr = malloc(2 * sizeof(char *));
		if (!new_arr)
			return (NULL);
		new_arr[0] = strdup(new_str);
		new_arr[1] = NULL;
		*arr = new_arr;
		return (new_arr);
	}
	while ((*arr)[i])
		i++;
	new_arr = malloc((i + 2) * sizeof(char *));
	if (!new_arr)
		return (NULL);
	for (int j = 0; j < i; j++)
		new_arr[j] = (*arr)[j];
	new_arr[i] = strdup(new_str);
	new_arr[i + 1] = NULL;
	free(*arr);
	*arr = new_arr;
	return (new_arr);
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*cmd;
	t_token		*current;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->next = NULL;
	cmd->append = 0;
	cmd->heredoc = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			ft_addstr(&cmd->args, current->value);
		else if (current->type == TOKEN_REDIR_IN && current->next)
		{
			if (cmd->infile)
				free(cmd->infile);
			cmd->infile = ft_strdup(current->next->value);
			current = current->next;
		}
		else if (current->type == TOKEN_REDIR_OUT && current->next)
		{
			if (cmd->outfile)
				free(cmd->outfile);
			cmd->outfile = ft_strdup(current->next->value);
			current = current->next;
		}
		else if (current->type == TOKEN_REDIR_APPEND && current->next)
		{
			if (cmd->outfile)
				free(cmd->outfile);
			cmd->outfile = ft_strdup(current->next->value);
			cmd->append = 1;
			current = current->next;
		}
		else if (current->type == TOKEN_HEREDOC && current->next)
		{
			if (cmd->heredoc)
				free(cmd->heredoc);
			cmd->heredoc = ft_strdup(current->next->value);
			current = current->next;
		}
		else if (current->type == TOKEN_PIPE)
		{
			cmd->next = parse_tokens(current->next);
			break ;
		}
		current = current->next;
	}
	return (cmd);
}

char	*extract_quoted_value(char *line, int *i)
{
	char	*value;
	int		start;
	char	quote;

	quote = line[*i];
	start = ++(*i);
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (ft_strdup(""));
	value = ft_substr(line, start, *i - start);
	(*i)++;
	if (!value)
		return (ft_strdup(""));
	return (value);
}

char	*extract_word_value(char *line, int *i)
{
	char	*value;
	int		start;
	char	quote;

	start = *i;
	while (line[*i] && line[*i] != ' ' && !is_special_char(line, *i))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			quote = line[*i++];
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (line[*i])
				(*i)++;
		}
		else
			(*i)++;
	}
	value = ft_substr(line, start, *i - start);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

void	process_and_add_token(t_token **token_list, char *line, int *i)
{
	t_token_type	type;
	char			*value;

	if (is_special_char(line, *i))
	{
		type = get_token_type(line, i);
		value = ft_strdup("");
	}
	else
	{
		type = TOKEN_WORD;
		if (line[*i] == '\'' || line[*i] == '\"')
			value = extract_quoted_value(line, i);
		else
			value = extract_word_value(line, i);
	}
	if (value)
		push_back(token_list, value, type);
}

void	free_command_list(t_command **cmd_list)
{
	t_command	*current;
	t_command	*next;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next = current->next;
		if (current->args)
		{
			for (int i = 0; current->args[i]; i++)
				free(current->args[i]);
			free(current->args);
		}
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		if (current->heredoc)
			free(current->heredoc);
		free(current);
		current = next;
	}
	*cmd_list = NULL;
}

void	tokenize_line(char *line)
{
	t_token		*token_list;
	t_command	*cmds;
	t_command	*current;
	int			i;

	token_list = NULL;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		process_and_add_token(&token_list, line, &i);
	}
	cmds = parse_tokens(token_list);
	current = cmds;
	while (current)
	{
		printf("Command: ");
		for (int j = 0; current->args && current->args[j]; j++)
			printf("%s ", current->args[j]);
		printf("\nInput: %s\nOutput: %s\nAppend: %d\n",
			current->infile ? current->infile : "None",
			current->outfile ? current->outfile : "None", current->append);
		printf("Heredoc: %s\n\n", current->heredoc ? current->heredoc : "None");
		current = current->next;
	}
	free_token_list(&token_list);
	free_command_list(&cmds);
}
