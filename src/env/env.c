/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:47:22 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/27 14:02:22 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_to_str(t_env *env)
{
	char	**str_env;
	int		i;

	i = 0;
	str_env = (char **)malloc(sizeof(char *) * (env_size(env) + 1));
	if (!str_env)
		return (NULL);
	while (env)
	{
		str_env[i] = ft_strdup(env->value);
		if (!str_env[i])
		{
			while (i--)
				free(str_env[i]);
			free(str_env);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	str_env[i] = NULL;
	return (str_env);
}

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

int	print_sorted_env(t_env *env)
{
	char	**env_arr;
	int		i;

	env_arr = env_to_str(env);
	i = 0;
	if (!env_arr)
		return (FAILURE);
	sort_env(env_arr);
	while (env_arr[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(env_arr[i++], STDOUT_FILENO);
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
	int		i;

	i = 0;
	if (!env || !envp)
		return (0);
	*env = NULL;
	while (envp[i])
		push_env_back(env, envp[i++]);
	return (1);
}
