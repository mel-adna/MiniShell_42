/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:02:32 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/19 16:53:58 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(t_command *cmds, t_fd *fd, char **envp)
{
	if (fd->fdin >= 0)
	{
		if (fd->fdin == -1)
		{
			close_fds(fd);
			exit(EXIT_FAILURE);
		}
		if (dup2(fd->fdin, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2");
			close_fds(fd);
			exit(EXIT_FAILURE);
		}
	}
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
	// close_fds(fd);
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
		if (current->infile)
			if (open_file(&fd, current, 1) == 0)
				return (0);
		if (current->outfile)
			if (open_file(&fd, current, 0) == 0)
				return (0);
		if (cmds->pipe)
			if (pipe(fd.pipefd) == -1)
				return (perror("minishell: pipe"), 0);
		if (is_builtin(current->args[0]))
			exec_builtin(current->args ,env, &cmds, fd);
		else
			ft_exec_cmd(&fd, current, envp);
		current = current->next;
	}
	wait_children(cmds);
	return (1);
}
