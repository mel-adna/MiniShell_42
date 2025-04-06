/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:08:53 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/06 18:25:38 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handel_signal_exit(int status)
{
	int	sig_exit;

	sig_exit = 0;
	sig_exit = WTERMSIG(status);
	if (sig_exit == SIGINT)
		return (130);
	if (sig_exit == SIGQUIT)
		return (131);
	return (128 + sig_exit);
}

void	wait_children(t_command *cmds)
{
	t_command	*current;
	int			status;

	current = cmds;
	while (current)
	{
		if (current->pid != -1)
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
				g_exit_code = handel_signal_exit(status);
		}
		current = current->next;
	}
}
