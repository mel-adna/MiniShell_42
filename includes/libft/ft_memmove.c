/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:29:14 by mel-adna          #+#    #+#             */
/*   Updated: 2024/11/18 15:20:16 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	if (dest == src)
		return (dest);
	if (dest > src)
	{
		while (len--)
			((unsigned char *)dest)[len] = ((const unsigned char *)src)[len];
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
