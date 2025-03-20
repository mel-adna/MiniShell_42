/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:59:36 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/20 00:14:43 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_signals(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_command *cmds = NULL;
	char	*input;
	t_env 	*env;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
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
		if (*input)
			add_history(input);
		cmds = parse(input, &env);
		if(!cmds)
		{
			free(input);
			continue ;
		}
		exec(cmds, &env);
		free_command_list(&cmds);
	}
}
