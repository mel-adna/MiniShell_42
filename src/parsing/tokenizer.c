/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:00:00 by username          #+#    #+#             */
/*   Updated: 2025/04/06 13:35:08 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_env(char *l, int *i, t_env **e, char **r)
{
	(*i)++;
	if (l[*i] == '?')
	{
		(*i)++;
		*r = add_result(*r, ft_itoa(g_exit_code));
		return ;
	}
	if (ft_isdigit(l[*i]))
	{
		(*i)++;
		return ;
	}
	process_env_var(l, i, e, r);
}

static char	*handle_quotes(char *line, int *i, t_env **env, char quote)
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

static void	handle_char(char c, char **v)
{
	char	t[2];
	char	*o;

	t[0] = c;
	t[1] = '\0';
	o = *v;
	*v = ft_strjoin(*v, t);
	free(o);
}

static void	process_word(char *l, int *i, t_env **e, char **v)
{
	char	*q;
	char	*t;

	if (l[*i] == '"' || l[*i] == '\'')
	{
		q = &l[*i];
		t = handle_quotes(l, i, e, *q);
		if (t)
			*v = add_result(*v, t);
	}
	else if (l[*i] == '$' && (ft_isalnum(l[*i + 1]) || l[*i + 1] == '_' 
			|| l[*i + 1] == '?'))
		expand_env(l, i, e, v);
	else if (l[*i] == '~' && (l[*i + 1] == '/' || !l[*i + 1] 
			|| l[*i + 1] == ' ') && (*i == 0 || l[*i - 1] == ' '))
	{
		(*i)++;
		*v = add_result(*v, ft_strdup(getenv("HOME")));
	}
	else
		handle_char(l[(*i)++], v);
}

void	process_and_add_token(t_token **t, char *l, int *i, t_env **e)
{
	t_token_type	type;
	char			*v;
	int				has_quotes;

	has_quotes = 0;
	if (is_special_char(l, *i))
	{
		type = get_token_type(l, i);
		push_back(t, ft_strdup(""), type);
	}
	else
	{
		type = TOKEN_WORD;
		v = ft_strdup("");
		while (l[*i] && l[*i] != ' ' && !is_special_char(l, *i))
		{
			if (l[*i] == '\'' || l[*i] == '"')
				has_quotes = 1;
			process_word(l, i, e, &v);
		}
		if ((v && *v) || has_quotes)
			push_back(t, v, type);
		else
			free(v);
	}
}
