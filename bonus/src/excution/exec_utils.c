/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 16:23:52 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/19 15:51:20 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

int	open_infile(t_fd *fd, t_command *cmd)
{
	if (cmd->infile)
	{
		fd->fdin = open(cmd->infile, O_RDONLY);
		if (fd->fdin < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->infile);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

int	open_outfile(t_fd *fd, t_command *cmd)
{
	int	i;

	if (fd->fdout >= 0)
		close(fd->fdout);
	i = 0;
	while (cmd->outfile[i])
	{
		if (cmd->append)
			fd->fdout = open(cmd->outfile[i], O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			fd->fdout = open(cmd->outfile[i], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (fd->fdout < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(cmd->outfile[i]);
			close(fd->fdin);
			return (FAILURE);
		}
		if (cmd->outfile[i + 1])
			close(fd->fdout);
		i++;
	}
	return (SUCCESS);
}

int	open_redir(t_command *current, t_fd *fd)
{
	if (current->infile)
		open_infile(fd, current);
	if (current->outfile && current->outfile[0])
		if (open_outfile(fd, current) == FAILURE)
			return (FAILURE);
	if (current->pipe)
		if (pipe(fd->pipefd) == -1)
			return (perror("minishell: pipe"), FAILURE);
	if (current->heredoc && current->heredoc[0])
	{
		if (fd->fdin >= 0)
			close(fd->fdin);
		fd->fdin = open("/tmp/here_doc", O_RDONLY);
		if (fd->fdin < 0)
		{
			ft_putstr_fd("minishell: ", 2);
			perror("/tmp/here_doc");
			return (FAILURE);
		}
	}
	return (SUCCESS);
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
