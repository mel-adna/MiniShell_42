/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:59:36 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/14 23:45:31 by mel-adna         ###   ########.fr       */
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
	char	*input;
	t_minsh	minsh;

	(void)argc;
	(void)argv;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	env_init(&minsh, envp);
	increment_shell_lvl(&minsh);
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
		if (parse(input))
		{
			free(input);
			continue ;
		}
	}
}
