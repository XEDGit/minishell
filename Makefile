NAME := minishell

SRC := minishell.c

FLAGS := -Wextra -Wall -Werror

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

all:
	make
	./minishell