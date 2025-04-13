/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:48 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/13 17:33:03 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_env_var(char *line, int *i, t_env **env, char **result)
{
	char	*t;
	char	*v;
	int		j;

	j = *i;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	if (*i > j)
	{
		t = ft_substr(line, j, *i - j);
		if (t)
		{
			v = get_env_value(*env, t);
			if (v)
				*result = add_result(*result, ft_strdup(v));
			else
				*result = add_result(*result, ft_strdup(""));
			free(t);
		}
	}
}

void	handle_special_cases(char *line, int *i, t_env **env, char **value)
{
	char	*tmp;
	char	*home;

	if ((line[*i] == '$' && (line[*i + 1] == '"' || line[*i + 1] == '\'')))
		(*i)++;
	if (line[*i] == '"' || line[*i] == '\'')
	{
		tmp = handle_quotes(line, i, env, line[*i]);
		if (tmp)
			*value = add_result(*value, tmp);
	}
	else if (line[*i] == '$' && (ft_isalnum(line[*i + 1]) || line[*i + 1] == '_'
			|| line[*i + 1] == '?'))
		expand_env(line, i, env, value);
	else if (line[*i] == '~' && (line[*i + 1] == '/' || !line[*i + 1] || line[*i
				+ 1] == ' ') && (*i == 0 || line[*i - 1] == ' '))
	{
		(*i)++;
		home = get_env_value(*env, "HOME");
		if (home)
			*value = add_result(*value, ft_strdup(home));
	}
}
