/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:46 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/20 14:35:30 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_redirection(char **field, t_token *current)
{
	char	*new_value;

	if (!current->next || !current->next->value)
		return ;
	new_value = ft_strdup(current->next->value);
	if (!new_value)
		return ;
	if (*field)
		free(*field);
	*field = new_value;
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
	cmd->pid = -1;
	cmd->cmd_path = NULL;
	return (cmd);
}

static void	push_cmd_back(t_command **head, t_command *node)
{
	t_command	**last;

	last = head;
	if (!node || !head)
		return ;
	while (*last)
		last = &(*last)->next;
	*last = node;
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*cmd;
	t_command	*cmds;
	t_token		*token;

	cmds = NULL;
	cmd = init_command();
	token = tokens;
	if (!cmd)
		return (NULL);
	while (token)
	{
		if (token->type == TOKEN_WORD)
			cmd->args = ft_addstr(cmd->args, token->value);
		else if (token->type == TOKEN_PIPE)
		{
			cmd->pipe = 1;
			push_cmd_back(&cmds, cmd);
			cmd = init_command();
			if (!cmd)
				return (cmds);
		}
		else
		{
			process_redirection(cmd, token);
			if(token->next)
				token = token->next;
			else
				break;
		}
		token = token->next;
	}
	return (push_cmd_back(&cmds, cmd), cmds);
}
