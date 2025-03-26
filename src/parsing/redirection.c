/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:46 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/26 20:03:46 by mel-adna         ###   ########.fr       */
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

static void	handle_pipe(t_command **cmd, t_command **cmds)
{
	(*cmd)->pipe = 1;
	push_cmd_back(cmds, *cmd);
	*cmd = init_command();
}

t_command	*parse_tokens(t_token *tokens, t_command *cmds)
{
	t_command	*cmd;
	t_token		*token;

	cmd = init_command();
	if (cmd == NULL)
		return (NULL);
	token = tokens;
	while (token)
	{
		if (token->type == TOKEN_WORD)
			cmd->args = ft_addstr(cmd->args, token->value);
		else if (token->type == TOKEN_PIPE)
		{
			if (!cmd)
				return (cmds);
			handle_pipe(&cmd, &cmds);
		}
		else
			process_redirection(cmd, token);
		token = token->next;
	}
	push_cmd_back(&cmds, cmd);
	return (cmds);
}
