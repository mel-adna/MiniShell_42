CC = gcc
CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -lreadline
INCLUDES = -Iincludes
SRC = src/main.c
OBJ = $(SRC:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
