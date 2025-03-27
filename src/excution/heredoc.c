/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:38:13 by szemmour          #+#    #+#             */
/*   Updated: 2025/03/27 12:33:54 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	var_in_line(char *limiter, char *line)
{
	int	i;
	int	lm_len;

	if (!limiter || !line)
		return (0);
	lm_len = ft_strlen(limiter);
	if (lm_len == 0 || lm_len == 1)
		return (0);
	if ((limiter[0] == '\'' && limiter[lm_len - 1] == '\'')
		|| (limiter[0] == '\"' && limiter[lm_len - 1] == '\"'))
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ' && line[i
				+ 1] != '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	expand_variables(t_env *env, char *line, int fd)
{
	char	*var_value;
	char	*var_name;

	int i, (j);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] && ft_isalpha(line[i + 1]))
		{
			i++;
			j = 0;
			var_name = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1));
			if (!var_name)
				return ;
			while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
				var_name[j++] = line[i++];
			var_name[j] = '\0';
			var_value = get_env_value(env, var_name);
			if (var_value)
				ft_putstr_fd(var_value, fd);
			free(var_name);
		}
		else
			ft_putchar_fd(line[i++], fd);
	}
}

static char	*unqouted_limiter(char *limiter)
{
	char	*unqouted_lm;
	char	*tmp;
	int		len;

	unqouted_lm = NULL;
	if ((limiter[0] == '\'' || limiter[0] == '\"') && ft_strlen(limiter) > 1)
	{
		len = ft_strlen(limiter);
		if (limiter[0] == limiter[len - 1])
		{
			unqouted_lm = ft_substr(limiter, 1, len - 2);
			if (!unqouted_lm)
				return (ft_strjoin(limiter, "\n"));
		}
		tmp = unqouted_lm;
		unqouted_lm = ft_strjoin(unqouted_lm, "\n");
		free(tmp);
		if (!unqouted_lm)
			return (ft_strjoin(limiter, "\n"));
		return (unqouted_lm);
	}
	return (ft_strjoin(limiter, "\n"));
}

static void	handle_heredoc_signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		close(STDIN_FILENO);
	}
}

int	ft_heredoc(char *limiter, t_env *env)
{
	int		fd[2];
	char	*unqouted_lm;
	char	*line;

	signal(SIGINT, handle_heredoc_signals);
	signal(SIGQUIT, SIG_IGN);
	unqouted_lm = unqouted_limiter(limiter);
	if (pipe(fd) == -1)
		return (free(unqouted_lm), perror("pipe"), -1);
	while (1)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line || ft_strcmp(line, unqouted_lm) == 0)
			break ;
		if (var_in_line(unqouted_lm, line))
			expand_variables(env, line, fd[1]);
		else
			ft_putstr_fd(line, fd[1]);
		free(line);
	}
	if (line)
		free(line);
	return (get_next_line(-1), close(fd[1]), free(unqouted_lm), fd[0]);
}
