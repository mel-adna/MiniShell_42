/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:58:56 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/13 17:58:57 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	tokenize_line(char *line)
{
	t_token	*token_list;
	t_token	*current;
	int		i;

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
	current = token_list;
	while (current)
	{
		printf("value: %s type: %d\n", current->value, current->type);
		current = current->next;
	}
	free_token_list(&token_list);
}
