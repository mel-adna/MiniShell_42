/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:02:32 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/12 17:42:32 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_process(t_command *cmd, t_fd *fd, t_env **env, char **envp)
{
	cmd_files_handler(cmd, fd);
	check_is_dir(cmd->args[0]);
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(cmd->args, env);
		exit_func(fd, g_exit_code);
	}
	if (!cmd->cmd_path || !ft_strcmp(cmd->args[0], ".."))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit_func(fd, NOTFOUND);
	}
	close(fd->pipefd[0]);
	execve(cmd->cmd_path, cmd->args, envp);
	perror("minishell: execve");
	exit_func(fd, FAILURE);
}

static void	ft_exec_cmd(t_fd *fd, t_command *cmds, t_env **env, char **envp)
{
	cmds->pid = fork();
	if (cmds->pid < 0)
	{
		perror("minishell: fork");
		return ;
	}
	if (cmds->pid == 0)
		child_process(cmds, fd, env, envp);
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

	if (builtin_files_handler(current, fd, &stdin_copy,
			&stdout_copy) == FAILURE)
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

t_command	*init_vars(t_command *cmds, char **envp, int *prv_pipe)
{
	*prv_pipe = 0;
	resolve_cmd_paths(envp, cmds);
	return (cmds);
}

void	exec(t_command **cmds, t_env **env, char **envp, t_fd *fd)
{
	t_command	*current;
	int			prv_pipe;

	current = init_vars(*cmds, envp, &prv_pipe);
	while (current)
	{
		if (current->pipe)
			prv_pipe = 1;
		if (current->heredoc)
			if (ft_heredoc(current->heredoc, *env) == FAILURE)
				return ;
		if (open_redir(current, fd) == FAILURE)
			return ;
		if (current->args && is_builtin(current->args[0]) && !current->pipe
			&& !prv_pipe)
			exec_bltin(current, env, fd);
		else if (current->args && !ft_strcmp(current->args[0], "exit")
			&& !current->pipe && !prv_pipe)
			ft_exit(current->args, cmds, env, fd);
		else if (current->args && current->args[0]
			&& ft_strcmp(current->args[0], "exit") != 0)
			ft_exec_cmd(fd, current, env, envp);
		current = current->next;
	}
	wait_children(*cmds);
}
