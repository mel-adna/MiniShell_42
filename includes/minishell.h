#ifndef MINISHELL_H
# define MINISHELL_H

# include <../libft/libft.h>
# include <fcntl.h>
# include <limits.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}						t_env;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_command
{
	char				**args;
	char				*outfile;
	char				*infile;
	char				*heredoc;
	char				*cmd_path;
	pid_t				pid;
	int					pipe;
	int					append;
	struct s_command	*next;
}						t_command;

typedef struct s_fd
{
	int					pipefd[2];
	int					fdin;
	int					fdout;
}						t_fd;

// ====================== Parsing ======================
t_command				*parse(char *input);
t_command				*tokenize_line(char *line);
int						is_special_char(char *line, int i);
t_token_type			get_token_type(char *line, int *i);
void					handle_signals(int sig);
int						check_redirect_errors(char *input);
char					**ft_addstr(char ***arr, char *new_str);
void					process_and_add_token(t_token **token_list, char *line,
							int *i);
t_command				*parse_tokens(t_token *tokens);

// ====================== env ======================
int						env_init(t_env **env, char **envp);
void					increment_shell_lvl(t_env *env);

// ====================== utils ======================
void					push_back(t_token **head, char *value,
							t_token_type type);

// ====================== Free Memo ======================
void					free_command_list(t_command **cmd_list);
void					free_token_list(t_token **token_list);

// ====================== Excution ======================
int						exec(t_command *cmds, t_env **env);
int						resolve_cmd_paths(char **envp, t_command *cmds);
void					push_env_back(t_env **head, char *value);
// ====================== Excution Utils ======================
void					wait_children(t_command *cmds);
int						open_file(t_fd *fd, t_command *cmd, int n);
void					close_fds(t_fd fd);
void					dup_file(t_fd fd, int newfd);
// ====================== Builtins ======================
int						env_size(t_env *env);
int						is_builtin(char *command);
int						exec_builtin(char **args, t_env **env);
int						ft_cd(char **args, t_env **env);
int						ft_echo(char **args);
int						ft_env(t_env *env);
int						ft_export(char **args, t_env **env);
int						ft_pwd(void);
int						ft_unset(char **args, t_env **env);
int						print_sorted_env(t_env *env);
char					*get_var_name(char *var);
char					**env_to_str(t_env *env);
char					*get_env_value(t_env *env, const char *key);

#endif
