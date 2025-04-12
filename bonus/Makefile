NAME = ../minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
INCLUDES = -Iincludes -Ilibft
LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = src/main/minishell.c src/env/env.c src/env/shell_lvl.c src/parsing/parse.c \
 	  src/tools/list_utils.c src/parsing/redirection.c src/parsing/p_errors.c \
	  src/parsing/tokenizer.c src/tools/free_mem.c src/parsing/utils.c \
	  src/parsing/ft_addstr.c src/main/signal.c src/parsing/helper_fun.c \
	  src/excution/cmd_path.c src/excution/exec.c src/excution/exec_utils.c \
	  src/built_ins/builtin_utils.c src/built_ins/cd.c src/built_ins/echo.c \
	  src/built_ins/env.c src/built_ins/export.c src/built_ins/pwd.c src/built_ins/unset.c \
	  src/built_ins/exit.c src/excution/heredoc.c src/excution/utils.c src/excution/error_handler.c \
	  includes/gnl/get_next_line.c includes/gnl/get_next_line_utils.c src/parsing/wildcard.c 

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c includes/minishell.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
