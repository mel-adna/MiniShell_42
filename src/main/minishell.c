/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:59:36 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/20 17:29:09 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	}
	reset_terminal();
	return (0);
}
