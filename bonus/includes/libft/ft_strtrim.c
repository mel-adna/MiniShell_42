/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:53:05 by mel-adna          #+#    #+#             */
/*   Updated: 2024/11/12 10:56:27 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		tlen;
	char	*trm;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1) - 1;
	while (s1[start] && *set && ft_strchr(set, s1[start]))
		start++;
	while (end >= start && *set && ft_strchr(set, s1[end]))
		end--;
	tlen = end - start + 1;
	trm = malloc(tlen + 1);
	if (!trm)
		return (NULL);
	ft_memcpy(trm, s1 + start, tlen);
	trm[tlen] = '\0';
	return (trm);
}
