/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:23:52 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/20 16:33:45 by szemmour         ###   ########.fr       */
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
		if (current->pid != -1)
		{
			if (waitpid(current->pid, &status, 0) == -1)
			{
				perror("minishell: waitpid");
				return ;
			}
			if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
				return ;
		}
		current = current->next;
	}
}

int	open_file(t_fd *fd, t_command *cmd, int n)
{
	if (n && cmd->infile)
	{
		fd->fdin = open(cmd->infile, O_RDONLY);
		if (fd->fdin < 0)
		{
			perror("minishell: open");
			return (0);
		}
	}
	else if (!n && cmd->outfile)
	{
		if (cmd->append)
			fd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd->fdout < 0)
		{
			perror("minishell: open");
			close(fd->fdin);
			return (0);
		}
	}
	return (1);
}

int	open_redir(t_command *current, t_fd *fd)
{
	if (current->infile)
		if (open_file(fd, current, 1) == 0)
			return (0);
	if (current->outfile)
		if (open_file(fd, current, 0) == 0)
			return (0);
	if (current->pipe)
		if (pipe(fd->pipefd) == -1)
			return (perror("minishell: pipe"), 0);
	return (1);
}

void	close_fds(t_fd *fd)
{
	if (fd->fdin > 0)
	{
		close(fd->fdin);
		fd->fdin = -1;
	}
	if (fd->fdout > 0)
	{
		close(fd->fdout);
		fd->fdout = -1;
	}
	if (fd->pipefd[0] > 0)
	{
		close(fd->pipefd[0]);
		fd->pipefd[0] = -1;
	}
	if (fd->pipefd[1] > 0)
	{
		close(fd->pipefd[1]);
		fd->pipefd[1] = -1;
	}
}

void	dup_file(t_fd *fd, int newfd)
{
	if (dup2(newfd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close_fds(fd);
		exit(EXIT_FAILURE);
	}
}
