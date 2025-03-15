/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:41 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/15 16:51:42 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	print_command_details(t_command *current)
// {
// 	int	j;
// 	int	k;

// 	j = 0;
// 	k = -1;
// 	while (current->args && current->args[j])
// 		printf("Command [%i]: %s \n", ++k, current->args[j++]);
// 	if (current->outfile)
// 		printf("Outfile: %s\n", current->outfile);
// 	else
// 		printf("Outfile: None\n");
// 	if (current->infile)
// 		printf("Infile: %s\n", current->infile);
// 	else
// 		printf("Infile: None\n");
// 	printf("Pipe: %d\n", current->pipe);
// 	if (current->heredoc)
// 		printf("Heredoc: %s\n\n", current->heredoc);
// 	else
// 		printf("Heredoc: None\n\n");
// }

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
}

t_command	*tokenize_line(char *line)
{
	t_token		*token_list;
	t_command	*cmds;
	// t_command	*current;
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
	// t_token		*token = token_list;
	// while (token)
	// {
	// 	printf("value: %s  type: %d\n", token->value, token->type);
	// 	token = token->next;
	// }
	// printf("\n\n\n\n\n\n");
	cmds = parse_tokens(token_list);
	// current = cmds;
	// while (current)
	// {
	// 	print_command_details(current);
	// 	current = current->next;
	// }
	free_token_list(&token_list);
	return cmds;
	// free_command_list(&cmds);
}
