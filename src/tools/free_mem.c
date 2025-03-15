/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:45:07 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/15 00:45:08 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_command_fields(t_command *cmd)
{
	int	i;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}
	if (cmd->infile)
		free(cmd->infile);
	if (cmd->outfile)
		free(cmd->outfile);
	if (cmd->heredoc)
		free(cmd->heredoc);
}

void	free_command_list(t_command **cmd_list)
{
	t_command	*current;
	t_command	*next;

	if (!cmd_list || !*cmd_list)
		return ;
	current = *cmd_list;
	while (current)
	{
		next = current->next;
		free_command_fields(current);
		free(current);
		current = next;
	}
	*cmd_list = NULL;
}

void	free_token_list(t_token **token_list)
{
	t_token	*current;
	t_token	*next;

	if (!token_list || !(*token_list))
		return ;
	current = *token_list;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*token_list = NULL;
}
