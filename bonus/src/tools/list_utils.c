/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:59:13 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/16 09:39:14 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

t_token	*create_node(char *value, t_token_type type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->value = value;
	node->next = NULL;
	node->prev = NULL;
	node->type = type;
	return (node);
}

void	push_back(t_token **head, char *value, t_token_type type)
{
	t_token	*tmp;
	t_token	*new;

	if (!value)
		return ;
	new = create_node(value, type);
	if (!new || !head)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	push_cmd_back(t_command **head, t_command *node)
{
	t_command	**last;

	last = head;
	if (!node || !head)
		return ;
	while (*last)
		last = &(*last)->next;
	*last = node;
}
