/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:27:54 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/18 13:51:49 by szemmour         ###   ########.fr       */
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
		if (env_var_name && !ft_strcmp(var, env_var_name))
		{
			free(env_var_name);
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->value);
			free(tmp);
			return ;
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
		return (1);
	i = 1;
	while (args[i])
	{
		if (!ft_isalnum(args[i][0]))
			printf("unset: `%s`: not a valid identifier\n", args[i]);
		else
			remove_env_var(args[i], env);
		i++;
	}
	return (0);
}
