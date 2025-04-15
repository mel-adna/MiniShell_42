/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 15:09:32 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/15 18:02:09 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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
	while (cmds)
	{
		if (cmds->args && cmds->args[0])
		{
			if (ft_strchr(cmds->args[0], '/') || !ft_strncmp(cmds->args[0],
					"./", 2))
				cmds->cmd_path = ft_strdup(cmds->args[0]);
			else if (paths)
				cmds->cmd_path = get_cmd_path(paths, cmds->args[0]);
		}
		cmds = cmds->next;
	}
	free_array(paths);
	return (1);
}
