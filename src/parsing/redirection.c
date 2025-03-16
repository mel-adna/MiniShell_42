/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:46 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/16 14:14:37 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_redirection(t_command *cmd, t_token *current)
{
	if (current->next)
	{
		if (current->type == TOKEN_REDIR_IN)
			cmd->infile = ft_strdup(current->next->value);
		else if (current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_APPEND)
		{
			cmd->outfile = ft_strdup(current->next->value);
			if (current->type == TOKEN_REDIR_APPEND)
				cmd->append = 1;
		}
		else if (current->type == TOKEN_HEREDOC)
			cmd->heredoc = ft_strdup(current->next->value);
	}
}

static t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	return (cmd);
}

static void	push_cmd_back(t_command **head, t_command *node)
{
	t_command	*tmp;

	if (!node || !head)
		return ;
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

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*cmds;
	t_command	*cmd;
	t_token		*current;

	cmds = NULL;
	cmd = init_command();
	if (!cmd)
		return (NULL);
	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			ft_addstr(&cmd->args, current->value);
		else if (current->type == TOKEN_PIPE)
		{
			cmd->pipe = 1;
			push_cmd_back(&cmds, cmd);
			cmd = init_command();
			if (!cmd)
				return (cmds);
		}
		else
		{
			process_redirection(cmd, current);
			if (current->next)
				current = current->next;
			else
				break;
		}
		current = current->next;
	}
	push_cmd_back(&cmds, cmd);
	return (cmds);
}
