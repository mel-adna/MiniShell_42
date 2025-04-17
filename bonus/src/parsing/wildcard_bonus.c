/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 11:04:36 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/17 14:54:37 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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

static void	int_function(struct dirent *entry, t_token **t, char *dir_path)
{
	char	*tmp;

	tmp = ft_strjoin(dir_path, "/");
	push_back(t, ft_strjoin(tmp, entry->d_name), TOKEN_WORD);
	free(tmp);
}

static int	process_matches(DIR *dir, char *pattern_only, char *dir_path,
		t_token **t)
{
	struct dirent	*entry;
	int				matched;

	matched = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (ft_fnmatch(pattern_only, entry->d_name) == 0
			&& !(entry->d_name[0] == '.' && pattern_only[0] != '.'))
		{
			matched = 1;
			if (ft_strcmp(dir_path, ".") == 0)
				push_back(t, ft_strdup(entry->d_name), TOKEN_WORD);
			else
				int_function(entry, t, dir_path);
		}
		entry = readdir(dir);
	}
	free(dir_path);
	free(pattern_only);
	closedir(dir);
	return (matched);
}

void	expand_wildcard(const char *pattern, t_token **t)
{
	DIR		*dir;
	char	*dir_path;
	char	*pattern_only;
	char	*slash;
	int		matched;

	dir_path = ft_strdup(".");
	pattern_only = ft_strdup(pattern);
	slash = ft_strrchr(pattern, '/');
	if (slash)
	{
		free(dir_path);
		dir_path = ft_substr(pattern, 0, slash - pattern);
		free(pattern_only);
		pattern_only = ft_strdup(slash + 1);
	}
	dir = opendir(dir_path);
	if (!dir)
		return (free(dir_path), free(pattern_only), push_back(t,
				ft_strdup(pattern), TOKEN_WORD));
	matched = process_matches(dir, pattern_only, dir_path, t);
	if (!matched)
		push_back(t, ft_strdup(pattern), TOKEN_WORD);
}
