/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:57:57 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/13 17:57:58 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_init(t_minsh *minsh, char **envp)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!envp || !envp[0])
		return (1);
	env = malloc(sizeof(t_env));
	if (!env)
		return (1);
	env->value = ft_strdup(envp[0]);
	env->next = NULL;
	minsh->env = env;
	i = 1;
	while (envp[i])
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (1);
		new->value = ft_strdup(envp[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
