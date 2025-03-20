/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:58:09 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/20 15:47:04 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	increment_shell_lvl(t_env *env)
{
	int		shlvl;
	char	*new_value;
	char	*shlvl_str;
	t_env	*current;

	shlvl = 0;
	current = env;
	while (current && ft_strncmp(current->value, "SHLVL=", 6) != 0)
		current = current->next;
	if (!current)
		return ;
	shlvl = ft_atoi(current->value + 6) + 1;
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return ;
	new_value = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if (!new_value)
		return ;
	free(current->value);
	current->value = new_value;
}
