/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:39:54 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/16 16:19:09 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nbr_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_export(char **args, t_env **env)
{
	t_env *tmp = *env;

	if (nbr_args(args) == 1)
	{
		if (ft_env(tmp))
			return (1);
	}
	push_env_back(env, args[1]);
	return (1);
}