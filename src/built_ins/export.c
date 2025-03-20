/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:19:36 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/20 15:21:49 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

char	*get_var_name(char *var)
{
	int		i;
	char	*var_name;

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
	int		start;
	char	quote;
	int		i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i] || !var[++i])
		return (NULL);
	if (var[i] == '\'' || var[i] == '\"')
	{
		quote = var[i++], start = i;
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

void	print_env_error(int errorn, char *var)
{
	int	i;

	i = 0;
	if (errorn == 3)
		ft_putstr_fd("export: not valid in this context: ", 2);
	else if (errorn == 2 || errorn == 0)
		ft_putstr_fd("export: not a valid identifier: ", 2);
	i = 0;
	while (var[i] && (var[i] != '=' || errorn == 0))
	{
		ft_putchar_fd(var[i], 2);
		i++;
	}
	ft_putchar_fd('\n', 2);
}

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
		return (NULL);
	val = var_name;
	var_name = ft_strjoin(val, "=");
	free(val);
	if (!var_name)
		return (NULL);
	val = ft_strjoin(var_name, var_value);
	free(var_name);
	return (val);
}

int	is_var_in_env(char *var, t_env *env)
{
	char	*var_name;
	char	*env_var_name;

	var_name = get_var_name(var);
	if (!var_name)
		return (0);
	while (env)
	{
		env_var_name = get_var_name(env->value);
		if (env_var_name && !ft_strcmp(var_name, env_var_name))
		{
			if (strchr(var, '='))
			{
				free(env->value);
				env->value = get_var(var);
			}
			return (free(env_var_name), free(var_name), 1);
		}
		if (env_var_name)
			free(env_var_name);
		env = env->next;
	}
	return (0);
}

int	is_valid_env_var(char *var)
{
	int	i;

	i = 0;
	if (var[0] == '=')
		return (0);
	if (ft_isdigit(var[0]))
		return (2);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (3);
		i++;
	}
	return (1);
}

int	ft_export(char **args, t_env **env)
{
	int		i;
	int		errorn;
	int		ret;
	char	*var;

	i = 1;
	ret = 0;
	if (!args[1])
		return (print_sorted_env(*env));
	while (args[i])
	{
		errorn = is_valid_env_var(args[i]);
		if (errorn != 1)
			print_env_error(errorn, args[i]);
		else if (!is_var_in_env(args[i], *env))
		{
			ret = 1;
			var = get_var(args[i]);
			push_env_back(env, var);
			free(var);
		}
		i++;
	}
	return (ret);
}
