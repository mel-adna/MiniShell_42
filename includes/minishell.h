/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:13:21 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/14 15:38:55 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "./gnl/get_next_line.h"
# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SUCCESS 0
# define FAILURE 1
# define NOTFOUND 127

extern int				g_exit_code;

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
	TOKEN_OR
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
t_command				*parse(char *inputs, t_env **env);
t_command				*tokenize_line(char *line, t_env **env);
int						is_special_char(char *line, int i);
t_token_type			get_token_type(char *line, int *i);
void					handle_signals(int sig);
int						check_redirect_errors(char *input, int i,
							char *filename);
char					**ft_addstr(char **arr, char *new_str);
void					process_and_add_token(t_token **token_list, char *line,
							int *i, t_env **env);
void					parse_tokens(t_token *tokens, t_command **cmds);
t_command				*init_command(void);
void					push_cmd_back(t_command **head, t_command *node);
char					*get_value(char *name, t_env **env);
char					*add_result(char *result, char *tmp);
void					process_env_var(char *l, int *i, t_env **e, char **r);
void					handle_special_cases(char *line, int *i, 
							t_env **env, char **value);
char					*handle_quotes(char *line, int *i, 
							t_env **env, char quote);
void					expand_env(char *line, int *i, t_env **env, 
							char **result);
void					skip_dollar(char *line, int *i);
int						embiguous_redirect(char *input, t_env *env);

// ====================== env ======================
int						env_init(t_env **env, char **envp);
void					increment_shell_lvl(t_env **env);

// ====================== utils ======================
void					push_back(t_token **head, char *value,
							t_token_type type);

// ====================== Free Memo ======================
void					free_command_list(t_command **cmd_list);
void					free_token_list(t_token **token_list);
void					free_env(t_env **env);
void					free_array(char **arr);

// ====================== Excution ======================
void					exec(t_command **cmds, t_env **env, char **envp,
							t_fd *fd);
int						resolve_cmd_paths(char **envp, t_command *cmds);
void					push_env_back(t_env **head, char *value);
void					init_fds(t_fd *fd);

// ====================== Excution Utils ======================
void					wait_children(t_command *cmds);
int						open_file(t_fd *fd, t_command *cmd, int n);
int						open_redir(t_command *current, t_fd *fd);
void					close_fds(t_fd *fd);
int						dup_stdout(t_fd *fd, int newfd);
int						dup_stdin(t_fd *fd, int newfd);

// ====================== Error Handler ======================
void					exit_func(t_fd *fd, int status);
int						check_is_dir(char *cmd);
int						builtin_files_handler(t_command *current, t_fd *fd,
							int *stdin_copy, int *stdout_copy);
void					cmd_files_handler(t_command *cmd, t_fd *fd);

// ====================== Builtins ======================
int						env_size(t_env *env);
int						is_builtin(char *command);
void					exec_builtin(char **args, t_env **env);
int						ft_cd(char **args, t_env **env);
int						ft_echo(char **args);
int						ft_env(t_env *env);
int						ft_export(char **args, t_env **env);
int						ft_pwd(void);
int						ft_unset(char **args, t_env **env);
void					ft_exit(char **args, t_command **cmds, t_env **env,
							t_fd *fd);
int						print_sorted_env(t_env *env);
char					*get_var_name(char *var);
char					*get_env_value(t_env *env, const char *key);
char					*get_var_value(char *var);
char					**env_to_str(t_env *env);
int						is_valid_env_var_name(char *var);
void					append_env_value(t_env *env, char *var);

// ====================== here doc ======================
int						ft_heredoc(char *limiter, t_env *env);
void					signal_herdoc(int sig);

// ====================== Signals Handling ======================
void					handle_signals(int sig);
void					setup_signals(void);
void					reset_terminal(void);
#endif
