#include "../../includes/minishell.h"

int	ft_env(t_env *env)
{
	if (!env)
		return (0);
	while (env)
	{
		ft_putendl_fd(env->value, 1);
		env = env->next;
	}
	return (1);
}