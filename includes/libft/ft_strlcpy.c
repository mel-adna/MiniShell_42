/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:29:01 by mel-adna          #+#    #+#             */
/*   Updated: 2024/11/17 08:52:18 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t destsize)
{
	size_t	src_len;
	size_t	c;

	src_len = ft_strlen(src);
	c = 0;
	if (destsize == 0)
		return (src_len);
	while (c < destsize - 1 && src[c] != '\0')
	{
		dst[c] = src[c];
		c++;
	}
	dst[c] = '\0';
	return (src_len);
}
