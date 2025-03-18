/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:58:09 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/17 16:48:13 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return size;
}

void	increment_shell_lvl(t_env *env)
{
	int		shlvl;
	char	*new_value;
	char	*shlvl_str;

	shlvl = 0;
	while (env)
	{
		if (ft_strncmp(env->value, "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(env->value + 6) + 1;
			break ;
		}
		env = env->next;
	}
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return ;
	new_value = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if (!new_value)
		return ;
	free(env->value);
	env->value = new_value;
}
