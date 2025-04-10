/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:18:50 by mel-adna          #+#    #+#             */
/*   Updated: 2025/02/11 12:43:48 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (-1);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t destsize)
{
	size_t	src_len;
	size_t	c;

	src_len = gnl_strlen(src);
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

char	*gnl_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	len = gnl_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*result;
	char	*start;
	size_t	total_len;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	total_len = gnl_strlen(s1) + gnl_strlen(s2);
	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	start = result;
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (start);
}
