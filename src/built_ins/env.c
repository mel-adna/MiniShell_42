#include "../../includes/minishell.h"

int ft_env(t_env *env)
{
    while (env)
    {
        ft_putendl_fd(env->value, 1);
        env = env->next;
    }
    return 1;
}