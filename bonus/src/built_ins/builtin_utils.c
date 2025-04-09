/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:50:54 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/06 17:27:16 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *command)
{
	return (!ft_strcmp(command, "cd") || !ft_strcmp(command, "echo")
		|| !ft_strcmp(command, "pwd") || !ft_strcmp(command, "env")
		|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset"));
}

void	exec_builtin(char **args, t_env **env)
{
	if (ft_strcmp(args[0], "echo") == 0)
		g_exit_code = ft_echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		g_exit_code = ft_cd(args, env);
	if (ft_strcmp(args[0], "pwd") == 0)
		g_exit_code = ft_pwd();
	if (ft_strcmp(args[0], "env") == 0)
		g_exit_code = ft_env(*env);
	if (ft_strcmp(args[0], "export") == 0)
		g_exit_code = ft_export(args, env);
	if (ft_strcmp(args[0], "unset") == 0)
		g_exit_code = ft_unset(args, env);
}

char	*get_var_name(char *var)
{
	int		i;
	char	*var_name;

	if (!var)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	var_name = (char *)malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		var_name[i] = var[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

char	*get_var_value(char *var)
{
	char (quote);
	int start, (i);
	if (!var)
		return (NULL);
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i] || !var[++i])
		return (NULL);
	if (var[i] == '\'' || var[i] == '\"')
	{
		quote = var[i++];
		start = i;
		while (var[i] && var[i] != quote)
			i++;
		if (!var[i])
			return (NULL);
	}
	else
	{
		start = i;
		while (var[i] && var[i] != ' ')
			i++;
	}
	return (ft_substr(var, start, i - start));
}

int	is_valid_env_var_name(char *var)
{
	int		i;
	char	*var_name;

	if (!var || var[0] == '\0')
		return (0);
	var_name = get_var_name(var);
	if (!var_name || var_name[0] == '\0')
		return (free(var_name), 0);
	if (var_name[0] == '-' && var_name[1] == '-')
		return (free(var_name), 0);
	if (!isalpha(var_name[0]) && var_name[0] != '_')
		return (free(var_name), 0);
	i = 1;
	while (var_name[i])
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (free(var_name), 0);
		i++;
	}
	return (free(var_name), 1);
}
