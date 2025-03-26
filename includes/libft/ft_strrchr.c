/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:28:52 by mel-adna          #+#    #+#             */
/*   Updated: 2024/11/18 15:25:28 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char	*lastchr = NULL;

	while (*str)
	{
		if (*str == (char)c)
			lastchr = str;
		str++;
	}
	if (*str == (char)c)
		return ((char *)str);
	return ((char *)lastchr);
}
