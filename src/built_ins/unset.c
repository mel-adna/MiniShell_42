/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:27:54 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/07 12:04:23 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_var(char *var)
{
	int	i;

	if (!var || var[0] == '\0')
		return (0);
	if (!var || var[0] == '\0')
		return (0);
	if (var[0] == '-' && var[1] == '-')
		return (0);
	if (!isalpha(var[0]) && var[0] != '_')
		return (0);
	i = 1;
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_env_var(char *var, t_env **env)
{
	char	*env_var_name;
	t_env	*prev;
	t_env	*tmp;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		env_var_name = get_var_name(tmp->value);
		if (!env_var_name)
			return ;
		if (!ft_strcmp(var, env_var_name))
		{
			free(env_var_name);
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			return (free(tmp->value), free(tmp));
		}
		free(env_var_name);
		prev = tmp;
		tmp = tmp->next;
	}
}

int	print_error(char *var, int errn)
{
	if (errn == 1)
	{
		ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(var, STDERR_FILENO);
		ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
		return (FAILURE);
	}
	ft_putstr_fd("minishell: unset: -", STDERR_FILENO);
	ft_putchar_fd(var[1], STDERR_FILENO);
	ft_putendl_fd(": invalid option", STDERR_FILENO);
	ft_putendl_fd("unset: usage: unset [-f] [-v] [name ...]", 2);
	return (2);
}

int	ft_unset(char **args, t_env **env)
{
	int	i;

	if (!args[1])
		return (SUCCESS);
	i = 1;
	while (args[i])
	{
		if (args[i][0] == '-' && (args[i][1] == '-' || ft_isalpha(args[i][1])))
		{
			g_exit_code = print_error(args[i], 2);
			i++;
			continue ;
		}
		if (!is_valid_var(args[i]))
			g_exit_code = print_error(args[i], 1);
		else
		{
			remove_env_var(args[i], env);
			g_exit_code = SUCCESS;
		}
		i++;
	}
	return (g_exit_code);
}
