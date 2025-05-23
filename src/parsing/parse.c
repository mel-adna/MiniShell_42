/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:12 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/15 12:43:02 by szemmour         ###   ########.fr       */
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
	while (input[i] == ' ' || input[i] == '\t' || input[i] == '\r')
		i++;
	if (input[i] == '|')
		return (g_exit_code = 258,
			ft_putendl_fd("syntax error near unexpected token ", 2), 1);
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] != '|')
		{
			i++;
			while (input[i] == ' ' || input[i] == '\t' || input[i] == '\r')
				i++;
			if (input[i] == '|')
				return (g_exit_code = 258,
					ft_putendl_fd("syntax error near unexpected token ", 2), 1);
			if (input[i] == '\0')
				return (g_exit_code = 258,
					ft_putendl_fd("syntax error near unexpected token ", 2), 1);
		}
		i++;
	}
	return (0);
}

t_command	*parse(char *input, t_env **env)
{
	t_command	*cmds;

	cmds = NULL;
	if (!input || !*input)
		return (NULL);
	if (is_open_quotes(input))
		return (g_exit_code = 258,
			ft_putendl_fd("syntax error near unexpected ", 2), NULL);
	if (embiguous_redirect(input, *env))
		return (g_exit_code = 258, ft_putendl_fd("ambiguous redirect", 2),
			NULL);
	if (check_redirect_errors(input, 0, NULL))
		return (NULL);
	if (check_pipe_errors(input))
		return (NULL);
	cmds = tokenize_line(input, env);
	return (cmds);
}
