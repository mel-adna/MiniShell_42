/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:48 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/12 19:03:00 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
