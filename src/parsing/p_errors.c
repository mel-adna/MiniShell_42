/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_errors.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:52 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/15 00:44:53 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_ambiguous_redirect(char *filename)
{
	if (!filename || !*filename)
		return (1);
	if (ft_strchr(filename, ' ') && filename[0] != '"')
		return (1);
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
	start = i;
	while (input[i] && input[i] != ' ' && input[i] != '>' && input[i] != '<'
		&& input[i] != '|')
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
		if ((input[i] == '>' && input[i + 1] != '>') || (input[i] == '<'
				&& input[i + 1] != '<'))
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (!input[i] || input[i] == '>' || input[i] == '<'
				|| input[i] == '|')
				return (ft_putendl_fd("Syntax error: filename!!", 1), 1);
			filename = extract_filename(&input[i]);
			if (is_ambiguous_redirect(filename))
				return (free(filename),
					ft_putendl_fd("Ambiguous redirect error", 1), 1);
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
		|| (line[i] == '<' && line[i + 1] == '<') || line[i] == '|'
		|| line[i] == '<' || line[i] == '>' || line[i] == ';');
}
