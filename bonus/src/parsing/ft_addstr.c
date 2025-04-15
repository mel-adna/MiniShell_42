/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:48:58 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/15 17:56:21 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

char	**ft_addstr(char **arr, char *new_str)
{
	int		i;
	char	**new_arr;

	i = 0;
	if (!arr)
	{
		new_arr = malloc(2 * sizeof(char *));
		if (!new_arr)
			return (NULL);
		new_arr[0] = ft_strdup(new_str);
		new_arr[1] = NULL;
		return (new_arr);
	}
	while (arr[i])
		i++;
	new_arr = malloc((i + 2) * sizeof(char *));
	if (!new_arr)
		return (NULL);
	ft_memcpy(new_arr, arr, i * sizeof(char *));
	new_arr[i] = ft_strdup(new_str);
	new_arr[i + 1] = NULL;
	free(arr);
	return (new_arr);
}
