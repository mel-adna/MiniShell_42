/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:02:32 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/08 15:02:42 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	child_process(t_command *cmds, t_fd *fd, char **envp)
{
	if (fd->fdin >= 0)
	{
		if (dup_stdin(fd, fd->fdin) == FAILURE)
			exit_func(fd, FAILURE);
	}
	if (cmds->infile &&  fd->fdin == -1)
		exit_func(fd, FAILURE);
	if (cmds->pipe)
		if (dup_stdout(fd, fd->pipefd[1]) == FAILURE)
			exit_func(fd, FAILURE);
	if (cmds->outfile)
		if (dup_stdout(fd, fd->fdout) == FAILURE)
			exit_func(fd, FAILURE);
	check_is_dir(cmds->args[0]);
	if (!cmds->cmd_path || !ft_strcmp(cmds->args[0], ".."))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmds->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit_func(fd, NOTFOUND);
	}
	close(fd->pipefd[1]);
	execve(cmds->cmd_path, cmds->args, envp);
	perror("minishell: execve");
	exit_func(fd, FAILURE);
}

static void	ft_exec_cmd(t_fd *fd, t_command *cmds, char **envp)
{
	cmds->pid = fork();
	if (cmds->pid < 0)
	{
		perror("minishell: fork");
		return ;
	}
	if (cmds->pid == 0)
		child_process(cmds, fd, envp);
	else
	{
		close(fd->pipefd[1]);
		if (fd->fdin != STDIN_FILENO)
			close(fd->fdin);
		if (!cmds->next)
			close(fd->pipefd[0]);
		fd->fdin = fd->pipefd[0];
	}
}

static int	exec_bltin(t_command *current, t_env **env, t_fd *fd)
{
	int	stdin_copy;
	int	stdout_copy;

	if (current->infile &&  fd->fdin == -1)
		return (g_exit_code = FAILURE ,FAILURE);
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (current->pipe)
		if (dup_stdout(fd, fd->pipefd[1]) == FAILURE)
			return (FAILURE);
	if (current->outfile)
		if (dup_stdout(fd, fd->fdout) == FAILURE)
			return (FAILURE);
	exec_builtin(current->args, env);
	if (dup_stdin(fd, stdin_copy) == FAILURE)
		return (FAILURE);
	if (dup_stdout(fd, stdout_copy) == FAILURE)
		return (FAILURE);
	close(stdin_copy);
	close(stdout_copy);
	if (fd->fdin != STDIN_FILENO)
		close(fd->fdin);
	if (fd->fdout != STDOUT_FILENO)
		close(fd->fdout);
	if (current->pipe)
	{
		close(fd->pipefd[1]);
		fd->fdin = fd->pipefd[0];
	}
	return (SUCCESS);
}

void	exec(t_command **cmds, t_env **env, char **envp)
{
	t_fd		fd;
	t_command	*current;
	int			count;

	count = 0;
	init_fds(&fd);
	if (!resolve_cmd_paths(envp, *cmds))
		ft_putendl_fd("minishell: command error!", 2);
	current = *cmds;
	while (current)
	{
		count++;
		if (open_redir(current, &fd) == FAILURE)
			return ;
		if (current->heredoc)
			fd.fdin = ft_heredoc(current->heredoc, *env);
		if (current->args && is_builtin(current->args[0]))
			exec_bltin(current, env, &fd);
		else if (current->args && !ft_strcmp(current->args[0], "exit"))
		{
			if (!current->pipe && count == 1)
				ft_exit(current->args, cmds, env, &fd);
		}
		else if (current->args)
			ft_exec_cmd(&fd, current, envp);
		current = current->next;
	}
	wait_children(*cmds);
}
