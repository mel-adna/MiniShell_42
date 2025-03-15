/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:02:32 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/15 16:40:14 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void open_file(t_fd *fd, t_command *cmd, int n)
{
    if (n && cmd->infile)
    {
        fd->fdin = open(cmd->infile, O_RDONLY);
        if (fd->fdin < 0)
            perror("open");
    }
    else if (!n && cmd->outfile)
    {
        if (cmd->append)
            fd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            fd->fdout = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd->fdout < 0)
        {
            perror("open");
            close(fd->fdin);
            exit(EXIT_FAILURE);
        }
    }
}

void close_fds(t_fd fd)
{
    if (fd.fdin > 0)
        close(fd.fdin);
    if (fd.fdout > 0)
        close(fd.fdout);
    if (fd.pipefd[0] > 0)
        close(fd.pipefd[0]);
    if (fd.pipefd[1] > 0)
        close(fd.pipefd[1]);
}

void dup_file(t_fd fd, int newfd)
{
    if (dup2(newfd, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        close_fds(fd);
        exit(EXIT_FAILURE);
    }
}

void child_process(t_command *cmds, t_fd fd, char **envp)
{
    if(cmds->infile){
        if(fd.fdin == -1)
        {
            close_fds(fd);
            exit(EXIT_FAILURE);
        }
        if (dup2(fd.fdin, STDIN_FILENO) == -1)
        {
            perror("dup2");
            close_fds(fd);
            exit(EXIT_FAILURE);
        }
    }
    if (cmds->pipe)
        dup_file(fd, fd.pipefd[1]);
    else if (cmds->outfile)
        dup_file(fd, fd.fdout);
    if (!cmds->cmd_path)
    {
        ft_putstr_fd(cmds->args[0], 2);
        ft_putendl_fd(": Command Not Found!", 2);
        close_fds(fd);
        exit(127);
    }
    close_fds(fd);
    execve(cmds->cmd_path, cmds->args, envp);
    perror("execve");
    exit(EXIT_FAILURE);
}

static void wait_children(t_command *cmds)
{
    t_command *current = cmds;
    int status;

    while (current)
    {
        if (waitpid(current->pid, &status, 0) == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        
        if (WIFEXITED(status) && WEXITSTATUS(status) == 127)
            exit(127);
        current = current->next;
    }
}

void ft_exec_cmd(t_fd *fd, t_command *cmds, char **envp)
{
    cmds->pid = fork();
    if (cmds->pid < 0)
    {
        perror("fork");
        return;
    }
    
    if (cmds->pid == 0)
        child_process(cmds, *fd, envp);
    else
    {
        close(fd->pipefd[1]);
        fd->pipefd[1] = -1;
        
        if (fd->fdin != STDIN_FILENO)
        {
            close(fd->fdin);
            fd->fdin = -1;
        }
        
        if (!cmds->next)
        {
            close(fd->pipefd[0]);
            fd->pipefd[0] = -1;
        }
        else
            fd->fdin = fd->pipefd[0];
    }
}

void exec(t_command *cmds, char **envp)
{
    t_fd fd;
    t_command *current;

    if (!resolve_cmd_paths(envp, cmds))
        ft_putendl_fd("ERROR: command error!", 2);
    
    fd.fdin = -1;
    fd.fdout = -1;
    fd.pipefd[0] = -1;
    fd.pipefd[1] = -1;
    
    current = cmds;
    while (current)
    {
        if (cmds->pipe)
        {
            if (pipe(fd.pipefd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }
        if (current->infile)
            open_file(&fd, current, 1);
        if (current->outfile)
            open_file(&fd, current, 0);
            
        ft_exec_cmd(&fd, current, envp);
        current = current->next;
    }
    wait_children(cmds);
}
