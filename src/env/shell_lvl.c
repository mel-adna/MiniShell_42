#include "../../includes/minishell.h"

void	increment_shell_lvl(t_minsh *minish)
{
	t_env	*env;
	int		shlvl;
	char	*new_value;
	char	*shlvl_str;

	shlvl = 0;
	env = minish->env;
	while (env)
	{
		if (ft_strncmp(env->value, "SHLVL=", 6) == 0)
		{
			shlvl = ft_atoi(env->value + 6) + 1;
			break ;
		}
		env = env->next;
	}
	shlvl_str = ft_itoa(shlvl);
	if (!shlvl_str)
		return ;
	new_value = ft_strjoin("SHLVL=", shlvl_str);
	free(shlvl_str);
	if (!new_value)
		return ;
	free(env->value);
	env->value = new_value;
}
