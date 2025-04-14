/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:24 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/14 11:14:39 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_env(char *line, int *i, t_env **env, char **result)
{
	(*i)++;
	if (line[*i] == '?')
	{
		(*i)++;
		*result = add_result(*result, ft_itoa(g_exit_code));
		g_exit_code = 0;
		return ;
	}
	if (ft_isdigit(line[*i]))
	{
		(*i)++;
		return ;
	}
	process_env_var(line, i, env, result);
}

char	*handle_quotes(char *line, int *i, t_env **env, char quote)
{
	char	*result;
	int		start;

	result = ft_strdup("");
	start = ++(*i);
	while (line[*i] && line[*i] != quote)
	{
		if (quote == '"' && line[*i] == '$' && (ft_isalnum(line[*i + 1])
				|| line[*i + 1] == '_' || line[*i + 1] == '?'))
		{
			if (*i > start)
				result = add_result(result, ft_substr(line, start, *i - start));
			expand_env(line, i, env, &result);
			start = *i;
		}
		else
			(*i)++;
	}
	if (*i > start)
		result = add_result(result, ft_substr(line, start, *i - start));
	if (line[*i] == quote)
		(*i)++;
	return (result);
}

static void	handle_char(char c, char **value)
{
	char	str[2];
	char	*tmp;

	str[0] = c;
	str[1] = '\0';
	tmp = *value;
	*value = ft_strjoin(*value, str);
	free(tmp);
}

static void	process_word(char *line, int *i, t_env **env, char **value)
{
	if (line[*i] == '$' || line[*i] == '~' || line[*i] == '"'
		|| line[*i] == '\'')
		handle_special_cases(line, i, env, value);
	else
		handle_char(line[(*i)++], value);
}

void	process_and_add_token(t_token **type, char *line, int *i, t_env **env)
{
	t_token_type	tmp;
	char			*vlaue;
	int				has_quotes;

	has_quotes = 0;
	if (is_special_char(line, *i))
	{
		tmp = get_token_type(line, i);
		push_back(type, ft_strdup(""), tmp);
	}
	else
	{
		tmp = TOKEN_WORD;
		vlaue = ft_strdup("");
		while (line[*i] && line[*i] != ' ' && !is_special_char(line, *i))
		{
			if (line[*i] == '\'' || line[*i] == '"')
				has_quotes = 1;
			process_word(line, i, env, &vlaue);
		}
		if ((vlaue && *vlaue) || has_quotes)
			push_back(type, vlaue, tmp);
		else
			free(vlaue);
	}
}
