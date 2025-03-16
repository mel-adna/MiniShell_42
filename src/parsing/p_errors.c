/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:52 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/16 21:54:57 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_semicolon(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		else if (input[i] == ';' && quote == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*extract_filename(char *input)
{
	char	*filename;
	int		i;
	int		start;

	filename = NULL;
	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '"' || input[i] == '\'')
		i++;
	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '>' && input[i] != '<'
		&& input[i] != '|' && !(input[i] == '"' || input[i] == '\''))
		i++;
	filename = strndup(&input[start], i - start);
	return (filename);
}

int	check_redirect_errors(char *input)
{
	int		i;
	char	*filename;

	i = 0;
	while (input[i])
	{
		if (check_semicolon(input))
			return (ft_putendl_fd("Syntax error!!", 1), 1);
		if ((input[i] == '>' && input[i + 1] != '>') || (input[i] == '<'
				&& input[i + 1] != '<'))
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (!input[i] || input[i] == '>' || input[i] == '<'
				|| input[i] == '|')
				return (ft_putendl_fd("Syntax error!!", 1), 1);
			filename = extract_filename(&input[i]);
			if (access(filename, F_OK) == -1 && (input[i] == '>' && input[i
					- 1] != '>') && !(input[i] == '<' && input[i - 1] != '<'))
				return (perror(filename), free(filename), 1);
			free(filename);
		}
		i++;
	}
	return (0);
}

int	is_special_char(char *line, int i)
{
	return ((line[i] == '&' && line[i + 1] == '&') 
		|| (line[i] == '|' && line[i + 1] == '|') 
		|| (line[i] == '>' && line[i + 1] == '>')
		|| (line[i] == '<' && line[i + 1] == '<') 
		|| line[i] == '|' || line[i] == '<' || line[i] == '>');
}
