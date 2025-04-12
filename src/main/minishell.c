/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:59:36 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/12 13:07:35 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		g_exit_code;

void	process_input(t_command **cmds, char *input, t_env **env)
{
	char	**envp;
	t_fd	fd;

	init_fds(&fd);
	envp = env_to_str(*env);
	if (*input)
		add_history(input);
	*cmds = parse(input, env);
	if (!*cmds)
	{
		free_command_list(cmds);
		free(input);
		free_array(envp);
		return ;
	}
	exec(cmds, env, envp, &fd);
	free_command_list(cmds);
	free(input);
	free_array(envp);
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
	increment_shell_lvl(&env);
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
	free_env(&env);
	reset_terminal();
	return (g_exit_code);
}
