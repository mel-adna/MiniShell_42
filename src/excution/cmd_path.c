/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:09:32 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/20 16:35:34 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_current_dir(char **envp)
{
	int		i;
	char	*pwd;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			pwd = ft_strjoin(":", envp[i] + 4);
			if (!pwd)
				return (NULL);
			return (pwd);
		}
		i++;
	}
	return (NULL);
}

static char	**get_paths(char **envp)
{
	int		i;
	char	*str;
	char	**paths;
	char	*pwd;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			pwd = get_current_dir(envp);
			str = ft_strjoin(envp[i], pwd);
			paths = ft_split(str + 5, ':');
			free(str);
			free(pwd);
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
	if (!paths || !cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
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
