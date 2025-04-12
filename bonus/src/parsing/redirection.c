/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:18 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/12 19:03:00 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static void	update_redirection(char **field, t_token *current)
{
	char	*new_value;

	if (!current || !current->next || !current->next->value)
		return ;
	new_value = ft_strdup(current->next->value);
	if (!new_value)
		return ;
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

static t_command	*handle_pipe(t_command *cmd, t_command **cmds)
{
	t_command	*command;

	cmd->pipe = 1;
	push_cmd_back(cmds, cmd);
	command = init_command();
	if (!command)
		return (NULL);
	return (command);
}

void	parse_tokens(t_token *tokens, t_command **cmds)
{
	t_command	*cmd;
	t_token		*token;

	cmd = init_command();
	token = tokens;
	if (!cmd)
		return ;
	while (token)
	{
		if (token->type == TOKEN_WORD)
			cmd->args = ft_addstr(cmd->args, token->value);
		else if (token->type == TOKEN_PIPE)
			cmd = handle_pipe(cmd, cmds);
		else
		{
			process_redirection(cmd, token);
			if (token->next)
				token = token->next;
			else
				break ;
		}
		token = token->next;
	}
	push_cmd_back(cmds, cmd);
}
