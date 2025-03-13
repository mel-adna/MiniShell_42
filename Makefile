NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
INCLUDES = -Iincludes -Ilibft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
SRC = src/main/minishell.c src/env/env.c src/env/shell_lvl.c src/parsing/parse.c src/tools/list_utils.c \
	src/parsing/tokens.c 
OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT) $(LDFLAGS)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c 
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all
