/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:19:36 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/06 13:28:16 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	process_env_var(char *l, int *i, t_env **e, char **r)
{
	char	*t;
	char	*v;
	int		j;

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
