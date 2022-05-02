NAME := minishell

SRC := src/minishell.c src/ft_printf/libftprintf.a

LIBS := -lreadline -L .brew/opt/readline/lib -I .brew/opt/readline/include

FLAGS := -g # -Wextra -Wall -Werror

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME) $(LIBS)

all:
	make
	./minishell