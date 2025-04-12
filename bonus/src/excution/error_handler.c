/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:20:26 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/12 19:03:00 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	error_path(char *msg, char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
}

int	check_is_dir(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (ft_strcmp(cmd, ".") == 0)
	{
		ft_putstr_fd("minishell: .: filename argument required\n",
			STDERR_FILENO);
		ft_putstr_fd(".: usage: . filename [arguments]\n", STDERR_FILENO);
		return (closedir(dir), exit(2), 1);
	}
	else if (dir && (ft_strchr(cmd, '/')))
		return (closedir(dir), error_path(": is a directory\n", cmd), exit(126),
			1);
	else if (dir)
		closedir(dir);
	else if ((ft_strchr(cmd, '/')) && access(cmd, F_OK) == -1)
	{
		error_path(": No such file or directory\n", cmd);
		return (exit(127), 1);
	}
	else if ((ft_strchr(cmd, '/')) && access(cmd, X_OK) == -1)
		return (error_path(": Permission denied\n", cmd), exit(126), 1);
	return (0);
}

void	exit_func(t_fd *fd, int status)
{
	close_fds(fd);
	g_exit_code = status;
	exit(g_exit_code);
}

int	builtin_files_handler(t_command *current, t_fd *fd, int *stdin_copy,
		int *stdout_copy)
{
	if (current->infile && fd->fdin == -1)
		return (g_exit_code = FAILURE, FAILURE);
	*stdin_copy = dup(STDIN_FILENO);
	*stdout_copy = dup(STDOUT_FILENO);
	if (current->pipe)
		if (dup_stdout(fd, fd->pipefd[1]) == FAILURE)
			return (FAILURE);
	if (current->outfile)
		if (dup_stdout(fd, fd->fdout) == FAILURE)
			return (FAILURE);
	return (SUCCESS);
}

void	cmd_files_handler(t_command *cmd, t_fd *fd)
{
	if (fd->fdin >= 0)
	{
		if (dup_stdin(fd, fd->fdin) == FAILURE)
			exit_func(fd, FAILURE);
	}
	if ((cmd->heredoc || cmd->infile) && fd->fdin == -1)
		exit_func(fd, FAILURE);
	if (cmd->outfile)
		if (dup_stdout(fd, fd->fdout) == FAILURE)
			exit_func(fd, FAILURE);
	if (cmd->pipe)
		if (dup_stdout(fd, fd->pipefd[1]) == FAILURE)
			exit_func(fd, FAILURE);
}
