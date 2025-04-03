/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:19:36 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/03 15:18:23 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_var(char *var)
{
	char	*var_name;
	char	*var_value;
	char	*val;

	var_name = get_var_name(var);
	if (!var_name)
		return (NULL);
	var_value = get_var_value(var);
	if (!var_value)
	{
		var_value = ft_strdup("");
		if (!var_value)
			return (free(var_name), NULL);
	}
	val = var_name;
	var_name = ft_strjoin(val, "=");
	free(val);
	if (!var_name)
		return (free(var_value), NULL);
	val = ft_strjoin(var_name, var_value);
	if (!val)
		return (free(var_name), free(var_value), NULL);
	free(var_name);
	free(var_value);
	return (val);
}

int	is_var_in_env(char *var, t_env *env)
{
	char	*env_var_name;
	char	*new_var;
	char	*var_name;

	var_name = get_var_name(var);
	if (!var_name)
		return (0);
	while (env)
	{
		env_var_name = get_var_name(env->value);
		if (env_var_name && !ft_strcmp(var_name, env_var_name))
		{
			free(env->value);
			new_var = get_var(var);
			if (new_var)
				env->value = new_var;
			return (free(env_var_name), free(var_name), 1);
		}
		if (env_var_name)
			free(env_var_name);
		env = env->next;
	}
	return (free(var_name), 0);
}

void	print_env_error(char *var)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
	g_exit_code = FAILURE;
}

int	is_valid_env_var(char *var)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = get_var_name(var);
	if (!var_name || var_name[0] == '\0' || (!ft_isalpha(var_name[0])
			&& var_name[0] != '_'))
	{
		if (var_name)
			free(var_name);
		return (0);
	}
	while (var_name[i] && var_name[i] != '=')
	{
		if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
			return (free(var_name), 0);
		i++;
	}
	return (free(var_name), 1);
}

int	is_valid_env_value(char *var)
{
	int		i;
	char	*var_value;

	i = 0;
	var_value = get_var_value(var);
	if (!var_value || !var_value[0] || (!ft_isalpha(var_value[0])
			&& var_value[0] != '_'))
	{
		if (var_value)
			free(var_value);
		return (0);
	}
	while (var_value[i] && var_value[i] != '=')
	{
		if (!ft_isalnum(var_value[i]) && var_value[i] != '_')
			return (free(var_value), 0);
		i++;
	}
	return (free(var_value), 1);
}

int	ft_export(char **args, t_env **env)
{
	char	*var;
	int		i;

	i = 1;
	if (!args[1])
		return (print_sorted_env(*env));
	while (args[i])
	{
		if (!is_valid_env_var(args[i]))
			print_env_error(args[i]);
		else if (is_valid_env_value(args[i]) && !is_var_in_env(args[i], *env))
		{
			g_exit_code = SUCCESS;
			var = get_var(args[i]);
			if (var)
			{
				push_env_back(env, var);
				free(var);
			}
		}
		i++;
	}
	return (g_exit_code);
}
