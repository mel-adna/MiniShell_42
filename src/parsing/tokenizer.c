/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 09:51:00 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/05 09:51:01 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	expand_env(char *l, int *i, t_env **e, char **r)
{
	int		j;
	char	*t;
	char	*v;

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
	j = *i;
	while (l[*i] && (ft_isalnum(l[*i]) || l[*i] == '_'))
		(*i)++;
	if (*i > j)
	{
		t = ft_substr(l, j, *i - j);
		if (t)
		{
			v = get_value(t, e);
			if (v)
				*r = add_result(*r, ft_strdup(v));
			else
				*r = add_result(*r, ft_strdup(""));
			free(t);
		}
	}
}

static char	*handle_quotes(char *l, int *i, t_env **e, char q)
{
	char	*r[3];
	int		j;

	r[0] = ft_strdup("");
	j = ++(*i);
	r[2] = NULL;
	while (l[*i] && l[*i] != q)
	{
		if (q == '"' && l[*i] == '$' && (ft_isalnum(l[*i + 1]) || l[*i
				+ 1] == '_' || l[*i + 1] == '?'))
		{
			if (*i > j)
			{
				r[1] = ft_substr(l, j, *i - j);
				r[0] = add_result(r[0], r[1]);
			}
			expand_env(l, i, e, &r[0]);
			j = *i;
		}
		else
			(*i)++;
	}
	if (*i > j)
	{
		r[1] = ft_substr(l, j, *i - j);
		r[0] = add_result(r[0], r[1]);
	}
	if (l[*i] == q)
		(*i)++;
	return (r[0]);
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
	char	*t;
	char	q;

	if (l[*i] == '"' || l[*i] == '\'')
	{
		q = l[*i];
		t = handle_quotes(l, i, e, q);
		if (t)
			*v = add_result(*v, t);
	}
	else if (l[*i] == '$' && (ft_isalnum(l[*i + 1]) || l[*i + 1] == '_' || l[*i
			+ 1] == '?'))
		expand_env(l, i, e, v);
	else if (l[*i] == '~' && (l[*i + 1] == '/' || !l[*i + 1] || l[*i
			+ 1] == ' ') && (*i == 0 || l[*i - 1] == ' '))
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
			process_word(l, i, e, &v);
		if (v && *v)
			push_back(t, v, type);
		else
			free(v);
	}
}
