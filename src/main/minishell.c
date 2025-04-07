/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:59:36 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/07 19:48:16 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"

// int		g_exit_code;

// void	process_input(t_command **cmds, char *input, t_env **env, char **envp)
// {
// 	if (*input)
// 		add_history(input);
// 	*cmds = parse(input, env);
// 	if (!*cmds)
// 	{
// 		free(input);
// 		return ;
// 	}
// 	exec(cmds, env, envp);
// 	free_command_list(cmds);
// 	free(input);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_command	*cmds;
// 	char		*input;
// 	t_env		*env;

// 	cmds = NULL;
// 	(void)argc;
// 	(void)argv;
// 	setup_signals();
// 	env_init(&env, envp);
// 	increment_shell_lvl(env);
// 	while (1)
// 	{
// 		input = readline("minishell> ");
// 		if (!input)
// 		{
// 			printf("Exiting...\n");
// 			break ;
// 		}
// 		process_input(&cmds, input, &env, envp);
// 	}
// 	reset_terminal();
// 	return (g_exit_code);
// }

#include "../../includes/minishell.h"

int		g_exit_code;

void	process_input(t_command **cmds, char *input, t_env **env, char **envp)
{
	if (*input)
		add_history(input);
	*cmds = parse(input, env);
	if (!*cmds)
	{
		free(input);
		return ;
	}
	exec(cmds, env, envp);
	free_command_list(cmds);
	free(input);
}

void	ll(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_command	*cmds;
	char		*input;
	t_env		*env;

	// atexit(ll);
	cmds = NULL;
	setup_signals();
	env_init(&env, envp);
	increment_shell_lvl(env);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		input = ft_strdup(argv[2]);
		process_input(&cmds, input, &env, envp);
		return g_exit_code;
	}
	while (1)
	{
		input = readline("minishell $");
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			exit(g_exit_code);
		}
		if (!input)
		{
			// printf("Exiting...\n");
			break ;
		}
		process_input(&cmds, input, &env, envp);
		// system ("leaks -q minishell");
		// system ("lsof -c minishell");
	}
	reset_terminal();
	return (g_exit_code);
}
