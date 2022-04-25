NAME := minishell

SRC := src/minishell.c src/printf/libftprintf.a

FLAGS := -g -lreadline -fsanitize=address # -Wextra -Wall -Werror

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all:
	make
	./minishell