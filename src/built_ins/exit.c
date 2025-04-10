/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:03:17 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/10 18:19:24 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	isllong(char *str, int sign, int start_idx)
{
	const char	*max_positive;
	const char	*max_negative;
	const char	*max_value;
	int			i;

	i = 0;
	max_positive = "9223372036854775807";
	max_negative = "9223372036854775808";
	if (sign > 0)
		max_value = max_positive;
	else
		max_value = max_negative;
	while (i < 19)
	{
		if (str[start_idx + i] > max_value[i])
			return (1);
		else if (str[start_idx + i] < max_value[i])
			return (0);
		i++;
	}
	return (0);
}

int	is_llong_min_max(char *str)
{
	int	digit_count;

	int start_idx, (i), (sign);
	i = 0;
	digit_count = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == 48)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	start_idx = i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit_count++;
		i++;
	}
	if (digit_count < 19)
		return (0);
	if (digit_count > 19)
		return (1);
	return (isllong(str, sign, start_idx));
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (is_llong_min_max(str))
		return (0);
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '-' && !str[i + 1])
		return (1);
	if (!str[i] || !ft_isdigit(str[i]))
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (str[i] == '\0');
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
	long long	exit_code;

	exit_code = 0;
	// ft_putendl_fd("exit", 2);
	if (args_count(args) > 1)
	{
		if (!is_number(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			free_command_list(cmds);
			free_env(env);
			close_fds(fd);
			exit(255);
		}
		if (args_count(args) > 2)
			return (g_exit_code = 1,
				ft_putendl_fd("minishell: exit: too many arguments", 2));
		exit_code = ft_atoi(args[1]);
	}
	free_command_list(cmds);
	free_env(env);
	close_fds(fd);
	exit(exit_code);
}
