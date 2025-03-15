/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:46 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/15 00:44:47 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_redirection(char **field, t_token *current)
{
	if (*field)
		free(*field);
	*field = ft_strdup(current->next->value);
}

static void	process_redirection(t_command *cmd, t_token *current,
		t_token **next)
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
		*next = current->next;
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
	cmd->next = NULL;
	cmd->append = 0;
	cmd->heredoc = NULL;
	cmd->pipe = 0;
	return (cmd);
}

t_command	*parse_tokens(t_token *tokens)
{
	t_command	*cmd;
	t_token		*current;
	t_token		*next;

	cmd = init_command();
	if (!cmd)
		return (NULL);
	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD)
			ft_addstr(&cmd->args, current->value);
		else if (current->type == TOKEN_PIPE)
		{
			cmd->next = parse_tokens(current->next);
			cmd->pipe = 1;
			break ;
		}
		else
			process_redirection(cmd, current, &next);
		current = next;
	}
	return (cmd);
}
