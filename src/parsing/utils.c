/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:41 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/20 14:24:59 by szemmour         ###   ########.fr       */
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
	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		process_and_add_token(&token_list, line, &i, env);
	}
	cmds = parse_tokens(token_list);
	free_token_list(&token_list);
	return cmds;
}
