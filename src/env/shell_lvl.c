/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:58:09 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/15 18:36:26 by szemmour         ###   ########.fr       */
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

void	handle_empty_env(t_env **env)
{
	char	*pwd;
	char	cwd[PATH_MAX];

	if (!env)
		return ;
	if (getcwd(cwd, sizeof(cwd)))
	{
		pwd = ft_strjoin("PWD=", cwd);
		if (pwd)
		{
			push_env_back(env, pwd);
			free(pwd);
		}
	}
	push_env_back(env, "SHLVL=1");
	push_env_back(env, "_=/usr/bin/env");
}

void	increment_shell_lvl(t_env **env)
{
	int		shlvl;
	char	*new_value;
	char	*shlvl_str;
	t_env	*current;

	shlvl = 0;
	if (!env || !*env)
		return (handle_empty_env(env));
	current = *env;
	while (current && ft_strncmp(current->value, "SHLVL=", 6) != 0)
		current = current->next;
	if (!current)
		return (handle_empty_env(env));
	shlvl = ft_atoi(current->value + 6) + 1;
	if (shlvl > 1000)
		shlvl = 1;
	if (shlvl < 0)
		shlvl = 0;
	shlvl_str = ft_itoa(shlvl);
	new_value = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if (!new_value)
		return ;
	free(current->value);
	current->value = new_value;
}
