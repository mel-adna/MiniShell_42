/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:50:54 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/19 14:58:28 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *command)
{
	return (!ft_strcmp(command, "cd") || !ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset")
		|| !ft_strcmp(command, "exit"));
}

int	exec_builtin(char **args, t_env **env, t_command **cmds, t_fd fd)
{
	int	result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args, env);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args[0], "env") == 0)
		result = ft_env(*env);
	if (ft_strcmp(args[0], "export") == 0)
		result = ft_export(args, env);
	if (ft_strcmp(args[0], "unset") == 0)
		result = ft_unset(args, env);
	if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args, cmds, env, fd);
	return (result);
}
