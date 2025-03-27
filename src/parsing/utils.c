/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:41 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/27 14:20:04 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
}

t_command	*tokenize_line(char *line, t_env **env)
{
	t_token		*token_list;
	t_command	*cmds;
	int			i;

	token_list = NULL;
	cmds = NULL;
	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		process_and_add_token(&token_list, line, &i, env);
	}
	parse_tokens(token_list, &cmds);
	free_token_list(&token_list);
	return (cmds);
}

t_command	*init_command(void)
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

char	*get_value(char *name, t_env **env)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
			return (ft_strdup(current->value + ft_strlen(name) + 1));
		current = current->next;
	}
	return (NULL);
}
