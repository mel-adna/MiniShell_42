/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:59:36 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/24 22:59:17 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_exit_status = 0;

// void	print_command_list(t_command *cmds)
// {
// 	t_command	*current;
// 	int			i;

// 	current = cmds;
// 	while (current)
// 	{
// 		i = 0;
// 		printf("Command: %s\n", current->args[0]);
// 		while (current->args[i])
// 		{
// 			printf("Arg %d: %s\n", i, current->args[i]);
// 			i++;
// 		}
// 		current = current->next;
// 	}
// }

void	process_input(t_command **cmds, char *input, t_env **env)
{
	if (*input)
		add_history(input);
	*cmds = parse(input, env);
	if (!*cmds)
	{
		free(input);
		return ;
	}
	exec(*cmds, env);
	// print_command_list(*cmds);
	// exit(0);
	free_command_list(cmds);
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmds;
	char		*input;
	t_env		*env;

	cmds = NULL;
	(void)argc;
	(void)argv;
	setup_signals();
	env_init(&env, envp);
	increment_shell_lvl(env);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("Exiting...\n");
			break ;
		}
		process_input(&cmds, input, &env);
		free(input);
	}
	reset_terminal();
	return (g_exit_status);
}
