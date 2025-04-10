/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:58:58 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/10 18:42:51 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	has_only_n(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	print_with_escapes(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '\\')
		{
			if (str[i + 1])
			{
				i++;
				if (str[i] == 'n')
					ft_putchar_fd('\n', 1);
				else if (str[i] == 't')
					ft_putchar_fd('\t', 1);
				else if (str[i] == 'r')
					ft_putchar_fd('\r', 1);
				else
					ft_putchar_fd(str[i], 1);
			}
			else
				ft_putchar_fd('\\', 1);
		}
		else
			ft_putchar_fd(str[i], 1);
		i++;
	}
}

int	ft_echo(char **args)
{
	int	n_option;
	int	i;

	n_option = 0;
	i = 1;
	while (args[i] && !ft_strncmp(args[i], "-n", 2) && has_only_n(args[i]))
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		print_with_escapes(args[i], 0);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_option)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
