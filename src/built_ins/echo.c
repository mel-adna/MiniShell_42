/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:58:58 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/27 15:33:49 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_exit_code(void)
{
	char	*str;

	str = ft_itoa(g_exit_code);
	if (!str)
		return (FAILURE);
	ft_putstr_fd(str, 1);
	free(str);
	return (SUCCESS);
}

int	ft_echo(char **args)
{
	int n_option, (i);
	n_option = 0;
	i = 1;
	while (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		n_option = 1;
		i++;
	}
	// if (args[i] && !ft_strcmp(args[i], "$?"))
	// {
	// 	if (print_exit_code() == FAILURE)
	// 		return (FAILURE);
	// 	i++;
	// }
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_option)
		ft_putchar_fd('\n', 1);
	return (SUCCESS);
}
