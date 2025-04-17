/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:42:43 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/16 10:15:26 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	append_env_value(t_env *env, char *var)
{
	char	*new_var;
	char	*var_value;

	var_value = get_var_value(var);
	if (!var_value)
		return ;
	new_var = ft_strjoin(env->value, var_value);
	if (!new_var)
		return (free(var_value));
	free(env->value);
	free(var_value);
	env->value = new_var;
}

char	*get_env_value(t_env *env, const char *key)
{
	char	*var_name;

	while (env)
	{
		var_name = get_var_name(env->value);
		if (ft_strcmp(var_name, key) == 0)
		{
			free(var_name);
			if (env->value)
				return (env->value + ft_strlen(key) + 1);
			else
				break ;
		}
		free(var_name);
		env = env->next;
	}
	return (NULL);
}

int	ft_env(t_env *env)
{
	if (!env)
		return (FAILURE);
	while (env)
	{
		if (ft_strchr(env->value, '='))
			ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	return (SUCCESS);
}
