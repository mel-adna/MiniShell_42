/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:25:58 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/18 16:54:10 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_env *env, const char *key)
{
	char	*var_name;

	while (env)
	{
		var_name = get_var_name(env->value);
		if (ft_strcmp(var_name, key) == 0)
		{
			free(var_name);
			return (env->value + ft_strlen(key));
		}
		free(var_name);
		env = env->next;
	}
	return (NULL);
}

int	update_oldpwd(t_env *env)
{
	char	*var_name;
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (!getcwd(cwd, sizeof(cwd)))
		return (0);
	while (env)
	{
		var_name = get_var_name(env->value);
		if (ft_strcmp("OLDPWD=", var_name) == 0)
		{
			oldpwd = ft_strjoin("OLDPWD=", cwd);
			if (!oldpwd)
				return (free(var_name), 0);
			free(env->value);
			free(var_name);
			env->value = oldpwd;
			return (1);
		}
		free(var_name);
		env = env->next;
	}
	return (0);
}

int	cd_home(t_env *env)
{
	char	*home;

	if (!update_oldpwd(env))
		return (0);
	home = get_env_value(env, "HOME=");
	if (!home || *home == '\0')
		return (ft_putendl_fd("cd: HOME not set", 2), 0);
	if (chdir(home) == -1)
		return (ft_putendl_fd("cd: cannot change directory", 2), 0);
	return (1);
}

int	cd_oldpwd(t_env *env)
{
	char	*oldpwd;

	oldpwd = get_env_value(env, "OLDPWD=");
	if (!update_oldpwd(env))
		return (ft_putendl_fd("cd: OLDPWD not set", 2), 0);
	return (0);
	if (chdir(oldpwd) == -1)
		return (ft_putendl_fd("cd: cannot change directory", 2), 0);
	ft_putendl_fd(oldpwd, 1);
	return (1);
}

int	ft_cd(char **args, t_env **env)
{
	if (!args[1] || args[1][0] == '~')
		return (cd_home(*env));
	if (args[1][0] == '-')
		return (cd_oldpwd(*env));
	update_oldpwd(*env);
	if (chdir(args[1]) == 0)
		return (1);
	ft_putstr_fd("cd: no such file or directory: ", 2);
	ft_putendl_fd(args[1], 2);
	return (0);
}
