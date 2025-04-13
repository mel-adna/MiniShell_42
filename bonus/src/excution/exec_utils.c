/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:23:52 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/13 11:52:29 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	open_file(t_fd *fd, t_command *cmd, int n)
{
	if (n && cmd->infile)
	{
		fd->fdin = open(cmd->infile, O_RDONLY);
		if (fd->fdin < 0)
		{
			ft_putstr_fd("minishell: open: ", 2);
			perror(cmd->infile);
			return (g_exit_code = FAILURE, FAILURE);
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
			ft_putstr_fd("minishell: open: ", 2);
			perror(cmd->outfile);
			close(fd->fdin);
			return (g_exit_code = FAILURE, FAILURE);
		}
	}
	return (g_exit_code = SUCCESS, SUCCESS);
}

int	open_redir(t_command *current, t_fd *fd)
{
	if (current->infile)
		open_file(fd, current, 1);
	if (current->outfile)
		if (open_file(fd, current, 0) == FAILURE)
			return (FAILURE);
	if (current->pipe)
		if (pipe(fd->pipefd) == -1)
			return (perror("minishell: pipe"), g_exit_code = FAILURE, FAILURE);
	if (current->heredoc)
	{
		fd->fdin = open("/tmp/here_doc", O_RDONLY | O_CREAT | O_APPEND, 0644);
		if (fd->fdin < 0)
		{
			ft_putstr_fd("minishell: open: ", 2);
			perror("/tmp/here_doc");
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

void	close_fds(t_fd *fd)
{
	if (fd->fdin >= 0)
	{
		close(fd->fdin);
		fd->fdin = -1;
	}
	if (fd->fdout >= 0)
	{
		close(fd->fdout);
		fd->fdout = -1;
	}
	if (fd->pipefd[0] >= 0)
	{
		close(fd->pipefd[0]);
		fd->pipefd[0] = -1;
	}
	if (fd->pipefd[1] >= 0)
	{
		close(fd->pipefd[1]);
		fd->pipefd[1] = -1;
	}
}

int	dup_stdout(t_fd *fd, int newfd)
{
	if (dup2(newfd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close_fds(fd);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	dup_stdin(t_fd *fd, int newfd)
{
	if (dup2(newfd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close_fds(fd);
		return (FAILURE);
	}
	return (SUCCESS);
}
