/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:38:13 by szemmour          #+#    #+#             */
/*   Updated: 2025/04/12 19:03:00 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

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

static char	*unquoted_limiter(char *limiter)
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
		tmp = ft_strjoin(unqouted_lm, "\n");
		free(unqouted_lm);
		tmp = unqouted_lm;
		if (!unqouted_lm)
			return (ft_strjoin(limiter, "\n"));
		return (unqouted_lm);
	}
	return (ft_strjoin(limiter, "\n"));
}

void	heredoc_handeler(char *limiter, t_env *env, int fd)
{
	char	*line;
	char	*unqouted_lm;

	signal(SIGINT, signal_herdoc);
	unqouted_lm = unquoted_limiter(limiter);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(0);
		if (!line || ft_strcmp(line, unqouted_lm) == 0)
			break ;
		if (var_in_line(unqouted_lm, line))
			expand_variables(env, line, fd);
		else
			ft_putstr_fd(line, fd);
		free(line);
	}
	if (line)
		free(line);
	get_next_line(-1);
	free(unqouted_lm);
}

int	ft_heredoc(char *limiter, t_env *env)
{
	int	pid;
	int	status;
	int	fd;

	status = 0;
	signal(SIGINT, SIG_IGN);
	if (access("/tmp/here_doc", F_OK) == 0)
		unlink("/tmp/here_doc");
	fd = open("/tmp/here_doc", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (perror("open"), exit(EXIT_FAILURE), FAILURE);
	pid = fork();
	if (pid == -1)
		return (close(fd), perror("fork"), exit(EXIT_FAILURE), FAILURE);
	if (pid == 0)
		heredoc_handeler(limiter, env, fd);
	else
	{
		waitpid(pid, &status, 0);
		status = WEXITSTATUS(status);
	}
	if (status == 1)
		return (close(fd), g_exit_code = 1, FAILURE);
	return (close(fd), SUCCESS);
}
