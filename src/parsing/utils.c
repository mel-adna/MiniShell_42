/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:41 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/15 00:44:42 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_command_details(t_command *current)
{
	int	j;
	int	k;

	j = 0;
	k = -1;
	while (current->args && current->args[j])
		printf("Command [%i]: %s \n", ++k, current->args[j++]);
	printf("Command type: %d\n", current->type);
	if (current->outfile)
		printf("Outfile: %s\n", current->outfile);
	else
		printf("Outfile: None\n");
	if (current->infile)
		printf("Infile: %s\n", current->infile);
	else
		printf("Infile: None\n");
	printf("Pipe: %d\n", current->pipe);
	if (current->heredoc)
		printf("Heredoc: %s\n\n", current->heredoc);
	else
		printf("Heredoc: None\n\n");
}

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
}

void	tokenize_line(char *line)
{
	t_token		*token_list;
	t_command	*cmds;
	t_command	*current;
	int			i;

	token_list = NULL;
	i = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		process_and_add_token(&token_list, line, &i);
	}
	cmds = parse_tokens(token_list);
	current = cmds;
	while (current)
	{
		print_command_details(current);
		current = current->next;
	}
	free_token_list(&token_list);
	free_command_list(&cmds);
}
