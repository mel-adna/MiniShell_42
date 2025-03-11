#include "../../includes/minishell.h"

void	handle_signals(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*input;
	t_minsh minsh;

	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	env_init(&minsh, envp);
	increment_shell_lvl(&minsh);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("Exiting...\n");
			break ;
		}
		if (*input)
			add_history(input);
		printf("Command: %s\n", input);
		free(input);
	}
	return (0);
}
