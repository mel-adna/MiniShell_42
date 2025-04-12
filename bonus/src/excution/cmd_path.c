/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:09:32 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/12 19:03:00 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	init_fds(t_fd *fd)
{
	fd->fdin = -1;
	fd->fdout = -1;
	fd->pipefd[0] = -1;
	fd->pipefd[1] = -1;
}

static char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

static char	*get_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*full_path;
	char	*temp;

	i = 0;
	if (!paths || !cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') || !ft_strncmp(cmd, "./", 2))
		return (ft_strdup(cmd));
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	resolve_cmd_paths(char **envp, t_command *cmds)
{
	char	**paths;

	if (!envp || !cmds)
		return (0);
	paths = get_paths(envp);
	if (!paths)
		return (0);
	while (cmds)
	{
		if (cmds->args && cmds->args[0])
			cmds->cmd_path = get_cmd_path(paths, cmds->args[0]);
		cmds = cmds->next;
	}
	free_array(paths);
	return (1);
}
