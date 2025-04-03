/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:44 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/03 15:14:32 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_env_value(char *line, int *i, t_env **env)
{
	char	*value;
	int		start;
	char	*name;

	value = NULL;
	if (line[0] == '$')
	{
		(*i)++;
		if (line[*i] == '?')
			if (line[*i] == '?')
				return ((*i)++, ft_itoa(g_exit_code));
	}
	start = ++(*i);
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	name = ft_substr(line, start, *i - start);
	if (!name)
		return (ft_strdup(""));
	value = get_value(name, env);
	if (!value)
		value = ft_strdup("");
	free(name);
	return (value);
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

static void	handle_quotes_in_word(char *line, int *i)
{
	char	quote;

	quote = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i])
		(*i)++;
}

char	*extract_word_value(char *line, int *i)
{
	char	*value;
	int		start;

	start = *i;
	while (line[*i] && line[*i] != ' ' && !is_special_char(line, *i))
	{
		if (line[*i] == '\'' || line[*i] == '\"')
			handle_quotes_in_word(line, i);
		else
			(*i)++;
	}
	value = ft_substr(line, start, *i - start);
	if (!value)
		return (ft_strdup(""));
	return (value);
}

void	process_and_add_token(t_token **token_list, char *line, int *i,
		t_env **env)
{
	t_token_type	type;
	char			*value;

	(void)env;
	if (is_special_char(line, *i))
	{
		type = get_token_type(line, i);
		value = ft_strdup("");
	}
	else
	{
		type = TOKEN_WORD;
		if (line[*i] == '$' && line[*i + 1] == '?')
			value = extract_env_value(line, i, env);
		else if (line[*i] == '\'' || line[*i] == '\"')
			value = extract_quoted_value(line, i);
		else
			value = extract_word_value(line, i);
	}
	if (value)
		push_back(token_list, value, type);
}
