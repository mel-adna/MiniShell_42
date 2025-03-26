/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:27:54 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/26 14:19:17 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (!is_valid_env_var(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("`: not a valid identifier", 2);
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
