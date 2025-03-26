/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:50 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/26 12:33:28 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token_type	get_token_type(char *line, int *i)
{
	if (line[*i] == '&' && line[*i + 1] == '&')
		return ((*i) += 2, TOKEN_AND);
	else if (line[*i] == '|' && line[*i + 1] == '|')
		return ((*i) += 2, TOKEN_OR);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		return ((*i) += 2, TOKEN_REDIR_APPEND);
	else if (line[*i] == '<' && line[*i + 1] == '<')
		return ((*i) += 2, TOKEN_HEREDOC);
	else if (line[*i] == '<')
		return ((*i)++, TOKEN_REDIR_IN);
	else if (line[*i] == '>')
		return ((*i)++, TOKEN_REDIR_OUT);
	else if (line[*i] == '|')
		return ((*i)++, TOKEN_PIPE);
	else
		return (TOKEN_WORD);
}

static void	ft_increment(int *open, int *i, int n)
{
	(*i)++;
	*open = n;
}

int	is_open_quotes(char *line)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i])
	{
		if (i > 0 && line[i - 1] == '\\')
			i++;
		else if (open == 0 && line[i] == '\"')
			ft_increment(&open, &i, 1);
		else if (open == 0 && line[i] == '\'')
			ft_increment(&open, &i, 2);
		else if ((open == 1 && line[i] == '\"') || (open == 2
				&& line[i] == '\''))
			ft_increment(&open, &i, 0);
		else
			i++;
	}
	return (open);
}

static int	check_pipe_errors(char *input)
{
	int	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
		return (ft_putendl_fd("Syntax error!!", 2), 1);
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] != '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '|')
				return (ft_putendl_fd("Syntax error!!", 2), 1);
			if (input[i] == '\0')
				return (ft_putendl_fd("Syntax error!!", 2), 1);
		}
		i++;
	}
	return (0);
}

t_command	*parse(char *input, t_env **env)
{
	t_command *cmds = NULL;
	
	if (!input || !*input)
		return (NULL);
	if (is_open_quotes(input))
		return (ft_putendl_fd("Syntax error!!", 2), NULL);
	if (check_redirect_errors(input))
		return (NULL);
	if (check_pipe_errors(input))
		return (NULL);
	cmds = tokenize_line(input, env);
	return (cmds);
}
