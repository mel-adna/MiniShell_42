/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 00:44:55 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/15 00:44:56 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_addstr(char ***arr, char *new_str)
{
	int		i;
	char	**new_arr;

	i = 0;
	if (*arr == NULL)
	{
		new_arr = malloc(2 * sizeof(char *));
		if (!new_arr)
			return (NULL);
		new_arr[0] = ft_strdup(new_str);
		new_arr[1] = NULL;
		*arr = new_arr;
		return (new_arr);
	}
	while ((*arr)[i])
		i++;
	new_arr = malloc((i + 2) * sizeof(char *));
	if (!new_arr)
		return (NULL);
	ft_memcpy(new_arr, *arr, i * sizeof(char *));
	new_arr[i] = ft_strdup(new_str);
	new_arr[i + 1] = NULL;
	free(*arr);
	*arr = new_arr;
	return (new_arr);
}
