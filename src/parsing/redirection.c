/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:46 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/15 15:01:31 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_redirection(char **field, t_token *current)
{
	if (*field)
		free(*field);
	*field = ft_strdup(current->next->value);
}

static void	process_redirection(t_command *cmd, t_token *current)
{
	if (current->next)
	{
		if (current->type == TOKEN_REDIR_IN)
		{
			update_redirection(&cmd->infile, current);
		}
		else if (current->type == TOKEN_REDIR_OUT
			|| current->type == TOKEN_REDIR_APPEND)
		{
			update_redirection(&cmd->outfile, current);
			if (current->type == TOKEN_REDIR_APPEND)
				cmd->append = 1;
		}
		else if (current->type == TOKEN_HEREDOC)
		{
			update_redirection(&cmd->heredoc, current);
		}
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
				current = current->next; // we don't need filename to be in **args
			else
				break;
		}
		current = current->next;
	}
	push_cmd_back(&cmds, cmd);
	return (cmds);
}
