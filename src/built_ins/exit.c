/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:03:17 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/25 13:25:48 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	args_count(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

void	ft_exit(char **args, t_command **cmds, t_env **env, t_fd *fd)
{
	ft_putendl_fd("exit", 1);
	if (args_count(args) > 1)
	{
		if (!is_number(args[1]) || args[1][0] == '\0')
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			g_exit_code = 255;
			free_command_list(cmds);
			free_env(env);
			close_fds(fd);
			exit(g_exit_code);
		}
		if (args_count(args) > 2)
			return (g_exit_code = 1,
				ft_putendl_fd("minishell: exit: too many arguments", 2));
		g_exit_code = ft_atoi(args[1]) % 256;
	}
	free_command_list(cmds);
	free_env(env);
	close_fds(fd);
	exit(g_exit_code);
}
