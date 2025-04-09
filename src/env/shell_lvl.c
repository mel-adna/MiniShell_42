/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:58:09 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/09 18:56:52 by szemmour         ###   ########.fr       */
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
	return (size);
}


char	**env_to_str(t_env *env)
{
	char	**str_env;
	int		i;

	i = 0;
	str_env = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	if (!str_env)
		return (NULL);
	while (env)
	{
		str_env[i] = ft_strdup(env->value);
		if (!str_env[i])
		{
			while (i--)
				free(str_env[i]);
			free(str_env);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	str_env[i] = NULL;
	return (str_env);
}

void	increment_shell_lvl(t_env *env)
{
	int		shlvl;
	char	*new_value;
	char	*shlvl_str;
	t_env	*current;

	shlvl = 0;
	current = env;
	while (current && ft_strncmp(current->value, "SHLVL=", 6) != 0)
		current = current->next;
	if (!current)
		return ;
	shlvl = ft_atoi(current->value + 6) + 1;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return ;
	new_value = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if (!new_value)
		return ;
	free(current->value);
	current->value = new_value;
}
