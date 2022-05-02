NAME := minishell

SRC := src/minishell.c src/ft_printf/libftprintf.a

LIBS := -lreadline

FLAGS := -g # -Wextra -Wall -Werror

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME) $(LIBS)

all:
	make
	./minishell