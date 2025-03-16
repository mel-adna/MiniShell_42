/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:47:22 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/16 15:55:52 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	push_env_back(t_env **head, char *value)
{
	t_env	*tmp;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node || !head)
		return ;
	node->value = strdup(value);
	node->next = NULL;
	if (*head == NULL)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

int	env_init(t_env **env, char **envp)
{
	int	i;

	i = 0;
	if (!env || !envp)
		return (1);
	while (envp[i])
	{
		push_env_back(env, envp[i]);
		i++;
	}
	return (0);
}
