/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:47:22 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/16 09:38:23 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	sort_env(char **env_arr)
{
	int		i;
	int		j;
	char	*tmp;

	if (!env_arr)
		return ;
	i = 0;
	while (env_arr[i])
	{
		j = 0;
		while (env_arr[j + 1])
		{
			if (ft_strcmp(env_arr[j], env_arr[j + 1]) > 0)
			{
				tmp = env_arr[j];
				env_arr[j] = env_arr[j + 1];
				env_arr[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_value(char *var_name, char *var_value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(var_name, STDOUT_FILENO);
	if (ft_strcmp(var_name, "OLDPWD") != 0)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd(var_value, STDOUT_FILENO);
		ft_putchar_fd('\"', STDOUT_FILENO);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	print_sorted_env(t_env *env)
{
	char	**env_arr;
	int		i;
	char	*var_name;
	char	*var_value;

	env_arr = env_to_str(env);
	i = 0;
	if (!env_arr)
		return (FAILURE);
	sort_env(env_arr);
	while (env_arr[i])
	{
		var_name = get_var_name(env_arr[i]);
		var_value = get_var_value(env_arr[i]);
		if (var_name)
		{
			print_value(var_name, var_value);
			free(var_name);
			free(var_value);
		}
		i++;
	}
	free_array(env_arr);
	return (SUCCESS);
}

void	push_env_back(t_env **head, char *value)
{
	t_env	*tmp;
	t_env	*node;

	if (!head || !value)
		return ;
	node = malloc(sizeof(t_env));
	if (!node)
		return ;
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node);
		return ;
	}
	node->next = NULL;
	if (!*head)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

int	env_init(t_env **env, char **envp)
{
	int	i;

	i = 0;
	if (!env || !envp)
		return (0);
	*env = NULL;
	while (envp[i])
		push_env_back(env, envp[i++]);
	return (1);
}
