/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 15:25:58 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/13 12:57:08 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	update_oldpwd(t_env *env)
{
	char	*var_name;
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (!getcwd(cwd, sizeof(cwd)))
		return (FAILURE);
	while (env)
	{
		var_name = get_var_name(env->value);
		if (!var_name)
			return (FAILURE);
		if (ft_strcmp("OLDPWD", var_name) == 0)
		{
			oldpwd = ft_strjoin("OLDPWD=", cwd);
			free(var_name);
			if (!oldpwd)
				return (FAILURE);
			free(env->value);
			env->value = oldpwd;
			return (SUCCESS);
		}
		free(var_name);
		env = env->next;
	}
	return (FAILURE);
}

int	update_pwd(t_env *env)
{
	char	*var_name;
	char	cwd[PATH_MAX];
	char	*pwd;

	if (!getcwd(cwd, sizeof(cwd)))
		return (FAILURE);
	while (env)
	{
		var_name = get_var_name(env->value);
		if (!var_name)
			return (FAILURE);
		if (ft_strcmp("PWD", var_name) == 0)
		{
			pwd = ft_strjoin("PWD=", cwd);
			free(var_name);
			if (!pwd)
				return (FAILURE);
			free(env->value);
			env->value = pwd;
			return (SUCCESS);
		}
		free(var_name);
		env = env->next;
	}
	return (FAILURE);
}

int	cd_home(t_env *env)
{
	char	*home;

	home = get_env_value(env, "HOME");
	if (!home || *home == '\0')
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), FAILURE);
	if (update_oldpwd(env) == FAILURE)
		return (FAILURE);
	if (chdir(home) == -1)
		return (ft_putendl_fd("minishell: cd: cannot change directory", 2),
			FAILURE);
	return (update_pwd(env));
}

int	cd_oldpwd(t_env *env)
{
	char	*oldpwd;

	oldpwd = get_env_value(env, "OLDPWD");
	if (!oldpwd || *oldpwd == '\0')
		return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2), FAILURE);
	if (update_oldpwd(env) == FAILURE)
		return (FAILURE);
	if (chdir(oldpwd) == -1)
		return (ft_putendl_fd("minishell: cd: cannot change directory", 2),
			FAILURE);
	if (update_pwd(env) == FAILURE)
		return (FAILURE);
	ft_putendl_fd(get_env_value(env, "PWD"), 1);
	return (SUCCESS);
}

int	ft_cd(char **args, t_env **env)
{
	if (args[1] && !args[1][0])
		return (SUCCESS);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (cd_home(*env));
	if (ft_strcmp(args[1], "-") == 0)
		return (cd_oldpwd(*env));
	update_oldpwd(*env);
	if (chdir(args[1]) == 0)
		return (update_pwd(*env));
	if (errno == ENAMETOOLONG)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": File name too long", 2);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	return (FAILURE);
}
