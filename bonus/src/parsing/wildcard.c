/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:04:36 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/09 11:28:23 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_fnmatch(const char *pattern, const char *string)
{
	if (*pattern == '\0')
	{
		if (*string == '\0')
			return (0);
		return (1);
	}
	if (*pattern == '*')
	{
		if (*(pattern + 1) == '\0')
			return (0);
		while (*string)
		{
			if (ft_fnmatch(pattern + 1, string) == 0)
				return (0);
			string++;
		}
		return (ft_fnmatch(pattern + 1, string));
	}
	if (*string == '\0')
		return (1);
	if (*pattern == '?' || *pattern == *string)
		return (ft_fnmatch(pattern + 1, string + 1));
	return (1);
}

static void	process_matches(DIR *dir, char *pattern_only, char *dir_path,
		t_token **t)
{
	struct dirent	*entry;
	char			*tmp;

	while ((entry = readdir(dir)) != NULL)
	{
		if (ft_fnmatch(pattern_only, entry->d_name) == 0)
		{
			if (ft_strcmp(dir_path, ".") == 0)
				push_back(t, ft_strdup(entry->d_name), TOKEN_WORD);
			else
			{
				tmp = ft_strjoin(dir_path, "/");
				push_back(t, ft_strjoin(tmp, entry->d_name), TOKEN_WORD);
				free(tmp);
			}
		}
	}
	closedir(dir);
	free(dir_path);
	free(pattern_only);
}

void	expand_wildcard(const char *pattern, t_token **t)
{
	DIR		*dir;
	char	*dir_path;
	char	*pattern_only;
	char	*slash;

	dir_path = ft_strdup(".");
	pattern_only = ft_strdup(pattern);
	if ((slash = ft_strrchr(pattern, '/')))
	{
		free(dir_path);
		dir_path = ft_substr(pattern, 0, slash - pattern);
		free(pattern_only);
		pattern_only = ft_strdup(slash + 1);
	}
	if (!(dir = opendir(dir_path)))
	{
		free(dir_path);
		free(pattern_only);
		return ;
	}
	process_matches(dir, pattern_only, dir_path, t);
}
