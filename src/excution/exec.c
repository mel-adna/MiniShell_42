/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:02:32 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/27 15:35:04 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (fd->fdin == -1)
			exit_func(fd, FAILURE);
		if (dup_stdin(fd, fd->fdin) == FAILURE)
			exit_func(fd, FAILURE);
	}
	if (cmds->pipe)
		if (dup_stdout(fd, fd->pipefd[1]) == FAILURE)
			exit_func(fd, FAILURE);
	if (cmds->outfile)
		if (dup_stdout(fd, fd->fdout) == FAILURE)
			exit_func(fd, FAILURE);
	if (!cmds->cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putendl_fd(cmds->args[0], 2);
		ft_putstr_fd(": command not found: ", 2);
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

	init_fds(&fd);
	if (!resolve_cmd_paths(envp, *cmds))
		ft_putendl_fd("minishell: command error!", 2);
	current = *cmds;
	while (current)
	{
		if (open_redir(current, &fd) == FAILURE)
			return ;
		if (current->heredoc)
			fd.fdin = ft_heredoc(current->heredoc, *env);
		if (current->args && is_builtin(current->args[0]))
			exec_bltin(current, env, &fd);
		else if (current->args && !ft_strcmp(current->args[0], "exit"))
		{
			if (!current->pipe)
				ft_exit(current->args, cmds, env, &fd);
		}
		else if (current->args && current->args[0] && current->args[0][0])
			ft_exec_cmd(&fd, current, envp);
		current = current->next;
	}
	wait_children(*cmds);
}
