/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:48 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/14 16:03:45 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*trim_env(char *s1)
{
	int		i;
	int		start;
	char	*value;

	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	i = 0;
	while (s1[i] && (s1[i] == ' ' || s1[i] == '\t' || s1[i] == '\r'))
		i++;
	start = i;
	while (s1[i] && !(s1[i] == ' ' || s1[i] == '\t' || s1[i] == '\r'))
		i++;
	value = ft_substr(s1, start, i - start);
	if(!value)
		return ft_strdup("");
	return (value);
}

void	process_env_var(char *line, int *i, t_env **env, char **result)
{
	char	*t;
	char	*v;
	int		j;
	char 	*res;

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
			{
				res = trim_env(v);
				if(res)
					*result = add_result(*result, res);
			}
			else
				*result = add_result(*result, ft_strdup(""));
			free(t);
		}
	}
}

void	skip_dollar(char *line, int *i)
{
	if ((line[*i] == '$' && line[*i + 1] == '"') || (line[*i] == '$' 
			&& line[*i + 1] == '\''))
		(*i)++;
}
