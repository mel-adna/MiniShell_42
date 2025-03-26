/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:26:52 by szemmour          #+#    #+#             */
/*   Updated: 2024/12/07 13:35:03 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *line)
{
	int		byte_read;
	char	*buffer;
	char	*tmp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byte_read = read(fd, buffer, BUFFER_SIZE);
	while (byte_read > 0)
	{
		buffer[byte_read] = '\0';
		tmp = line;
		line = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!line)
			return (free(buffer), NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
		byte_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (line);
}

char	*get_left_str(char *line)
{
	char	*left_str;
	char	*newline;

	if (!line)
		return (NULL);
	newline = ft_strchr(line, '\n');
	if (!newline)
		return (NULL);
	left_str = ft_strdup(newline + 1);
	return (left_str);
}

char	*ft_get_line(char *line)
{
	char	*result;
	char	*newline;
	size_t	len;

	if (!line)
		return (NULL);
	len = 0;
	newline = ft_strchr(line, '\n');
	if (!newline)
		len = ft_strlen(line);
	else
	{
		while (line[len] != '\n')
			len++;
		len++;
	}
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, line, len + 1);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*left_str = NULL;
	char		*line;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free(left_str), left_str = NULL, NULL);
	line = read_line(fd, left_str);
	left_str = NULL;
	if (!line || *line == '\0')
		return (free(line), NULL);
	result = ft_get_line(line);
	left_str = get_left_str(line);
	if (!result)
		return (free(left_str), free(line), left_str = NULL, NULL);
	free(line);
	return (result);
}
