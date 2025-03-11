#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <../libft/libft.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_minsh
{
	t_env			*env;
}					t_minsh;

// Parssing
char				**parse_arg(char *str);

// env
int					env_init(t_minsh *minsh, char **envp);
void				increment_shell_lvl(t_minsh *minish);

#endif
