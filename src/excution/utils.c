/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:08:53 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/16 09:33:44 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	wait_children(t_command *cmds)
{
	t_command	*current;
	int			status;

	current = cmds;
	while (current)
	{
		if (current->pid > 0)
		{
			if (waitpid(current->pid, &status, 0) == -1)
			{
				perror("minishell: waitpid");
				g_exit_code = EXIT_FAILURE;
				return ;
			}
			if (WIFEXITED(status))
				g_exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				g_exit_code = WTERMSIG(status) + 128;
				if (g_exit_code == 131)
					ft_putendl_fd("Quit: 3", STDERR_FILENO);
			}
		}
		current = current->next;
	}
}

void	signal_herdoc(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		exit(1);
	}
	else if (sig == SIGQUIT)
		return ;
}
