/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_fun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 13:19:36 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/09 18:27:26 by szemmour         ###   ########.fr       */
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
