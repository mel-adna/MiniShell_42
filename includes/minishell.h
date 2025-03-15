/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-adna <mel-adna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:00:38 by mel-adna          #+#    #+#             */
/*   Updated: 2025/03/15 00:39:55 by mel-adna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <../libft/libft.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_minsh
{
	t_env				*env;
}						t_minsh;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_END,
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
	t_token_type		type;
	char				*outfile;
	char				*infile;
	char				*heredoc;
	int					pipe;
	int					append;
	struct s_command	*next;
}						t_command;

// ====================== Parsing ======================
int						parse(char *input);
void					tokenize_line(char *line);
int						is_special_char(char *line, int i);
t_token_type			get_token_type(char *line, int *i);
void					handle_signals(int sig);
int						check_redirect_errors(char *input);
char					**ft_addstr(char ***arr, char *new_str);
void					process_and_add_token(t_token **token_list, char *line,
							int *i);
t_command				*parse_tokens(t_token *tokens);

// ====================== env ======================
int						env_init(t_minsh *minsh, char **envp);
void					increment_shell_lvl(t_minsh *minish);

// ====================== utils ======================
void					push_back(t_token **head, char *value,
							t_token_type type);

// ====================== Free Memo ======================
void					free_command_list(t_command **cmd_list);
void					free_token_list(t_token **token_list);

#endif
