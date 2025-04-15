/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   embiguous.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:52:08 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/15 17:56:21 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

static int	is_ambiguous(char *var_value)
{
	int	i;
	int	in_word;
	int	word_count;

	if (!var_value || !*var_value)
		return (1);
	i = 0;
	in_word = 0;
	word_count = 0;
	while (var_value[i])
	{
		if (var_value[i] != ' ' && !in_word)
		{
			in_word = 1;
			word_count++;
		}
		else if (var_value[i] == ' ')
			in_word = 0;
		i++;
	}
	return (word_count > 1);
}

static int	check_var_ambiguity(char *input, int *i, t_env *env)
{
	int		j;
	char	var_name[256];
	char	*value;

	(*i)++;
	j = 0;
	while ((ft_isalnum(input[*i]) || input[*i] == '_') && j < 255)
		var_name[j++] = input[(*i)++];
	var_name[j] = '\0';
	value = get_env_value(env, var_name);
	return (is_ambiguous(value));
}

int	embiguous_redirect(char *input, t_env *env)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			if (input[i] == '>' && input[i + 1] == '>')
				i++;
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '$' && check_var_ambiguity(input, &i, env))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
