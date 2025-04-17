/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/17 19:01:39 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_redirection(char ***list, t_token *current)
{
	int		i;
	char	**new_list;

	if (!*list)
	{
		*list = ft_calloc(2, sizeof(char *));
		if (!*list)
			return ;
		(*list)[0] = ft_strdup(current->next->value);
		return ;
	}
	i = 0;
	while ((*list)[i])
		i++;
	new_list = ft_calloc(i + 2, sizeof(char *));
	if (!new_list)
		return ;
	i = -1;
	while ((*list)[++i])
		new_list[i] = (*list)[i];
	new_list[i] = ft_strdup(current->next->value);
	new_list[i + 1] = NULL;
	free(*list);
	*list = new_list;
}

static void	process_redirection(t_command *cmd, t_token *current)
{
	if (current->next)
	{
		if (current->type == TOKEN_REDIR_IN)
		{
			if (current->next)
				cmd->infile = ft_strdup(current->next->value);
		}
		else if (current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_APPEND)
		{
			update_redirection(&cmd->outfile, current);
			if (current->type == TOKEN_REDIR_APPEND)
				cmd->append = 1;
			if (current->type == TOKEN_REDIR_OUT)
				cmd->append = 0;
		}
		else if (current->type == TOKEN_HEREDOC)
			update_redirection(&cmd->heredoc, current);
	}
}

static t_command	*handle_pipe(t_command *cmd, t_command **cmds)
{
	t_command	*command;

	cmd->pipe = 1;
	push_cmd_back(cmds, cmd);
	command = init_command();
	if (!command)
		return (NULL);
	return (command);
}

void	parse_tokens(t_token *tokens, t_command **cmds)
{
	t_command	*cmd;
	t_token		*token;

	cmd = init_command();
	token = tokens;
	if (!cmd)
		return ;
	while (token)
	{
		if (token->type == TOKEN_WORD)
			cmd->args = ft_addstr(cmd->args, token->value);
		else if (token->type == TOKEN_PIPE)
			cmd = handle_pipe(cmd, cmds);
		else
		{
			process_redirection(cmd, token);
			if (token->next)
				token = token->next;
			else
				break ;
		}
		token = token->next;
	}
	push_cmd_back(cmds, cmd);
}
