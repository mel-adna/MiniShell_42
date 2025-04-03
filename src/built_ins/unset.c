/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:27:54 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/03 17:45:18 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_var(char *var)
{
	int	i;

	i = 0;
	if (!var || var[0] == '\0' || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (0);
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

int	ft_unset(char **args, t_env **env)
{
	int	i;

	if (!args[1])
		return (SUCCESS);
	i = 1;
	while (args[i])
	{
		if (!is_valid_var(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd("`: not a valid identifier", STDERR_FILENO);
			g_exit_code = FAILURE;
		}
		else
		{
			remove_env_var(args[i], env);
			g_exit_code = SUCCESS;
		}
		i++;
	}
	return (g_exit_code);
}
