/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:50 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/15 00:44:51 by mel-adna         ###   ########.fr       */
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
	else if (line[*i] == ';')
		return ((*i)++, TOKEN_END);
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
		return (ft_putendl_fd("Syntax error: `|` at start", 1), 1);
	while (input[i])
	{
		if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '|')
				return (ft_putendl_fd("Syntax error: `|`", 1), 1);
			if (input[i] == '\0')
				return (ft_putendl_fd("Syntax error: `|` at end", 1), 1);
		}
		i++;
	}
	return (0);
}

int	parse(char *input)
{
	if (is_open_quotes(input))
		return (ft_putendl_fd("Error: Open quotes!", 1), 1);
	if (check_redirect_errors(input))
		return (1);
	if (check_pipe_errors(input))
		return (1);
	tokenize_line(input);
	return (1);
}
