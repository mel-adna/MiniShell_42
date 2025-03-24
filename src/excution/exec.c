/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:02:32 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/24 22:15:28 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_in_file(t_fd *fd)
{
	if (fd->fdin >= 0)
	{
		if (fd->fdin == -1)
		{
			close_fds(fd);
			return (0);
		}
		if (dup2(fd->fdin, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			close_fds(fd);
			return (0);
		}
	}
	return (1);
}

void	child_process(t_command *cmds, t_fd *fd, char **envp)
{
	if (!is_in_file(fd))
		exit(EXIT_FAILURE);
	if (cmds->pipe)
		dup_file(fd, fd->pipefd[1]);
	else if (cmds->outfile)
		dup_file(fd, fd->fdout);
	if (!cmds->cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putendl_fd(cmds->args[0], 2);
		close_fds(fd);
		exit(127);
	}
	close(fd->pipefd[1]);
	execve(cmds->cmd_path, cmds->args, envp);
	perror("minishell: execve");
	exit(EXIT_FAILURE);
}

void	ft_exec_cmd(t_fd *fd, t_command *cmds, char **envp)
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

void	exec_bltin(t_command *current, t_env **env, t_command **cmds, t_fd fd)
{
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (fd.fdin != STDIN_FILENO)
		dup2(fd.fdin, STDIN_FILENO);
	if (current->pipe)
		dup_file(&fd, fd.pipefd[1]);
	else if (current->outfile)
		dup_file(&fd, fd.fdout);
	exec_builtin(current->args, env, cmds, fd);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
	if (fd.fdin != STDIN_FILENO)
		close(fd.fdin);
	if (fd.fdout != STDOUT_FILENO)
		close(fd.fdout);
	if (current->pipe)
	{
		close(fd.pipefd[1]);
		fd.fdin = fd.pipefd[0];
	}
}

int	exec(t_command *cmds, t_env **env)
{
	t_fd		fd;
	t_command	*current;
	char		**envp;

	envp = env_to_str(*env);
	if (!resolve_cmd_paths(envp, cmds))
		ft_putendl_fd("minishell: command error!", 2);
	fd.fdin = -1;
	fd.pipefd[0] = -1;
	fd.pipefd[1] = -1;
	current = cmds;
	while (current)
	{
		if (!open_redir(current, &fd))
			return (0);
		if (is_builtin(current->args[0]))
			exec_bltin(current, env, &cmds, fd);
		else
			ft_exec_cmd(&fd, current, envp);
		current = current->next;
	}
	wait_children(cmds);
	return (1);
}
