/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:58:58 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/16 15:17:17 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nbr_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

int	ft_echo(char **args)
{
	int	n_option;
	int	i;

	n_option = 0;
	i = 1;
	if (nbr_args(args) == 1)
		return (ft_putchar_fd('\n', 1), 1);
	if (nbr_args(args) > 1)
	{
		while (args[i] && !ft_strncmp(args[i], "-n", ft_strlen(args[i])))
		{
			n_option++;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!n_option)
		ft_putchar_fd('\n', 1);
	return (1);
}
