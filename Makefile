NAME := minishell

SRC := src/minishell.c src/util/signal.c src/util/ft_split.c src/ft_printf/libftprintf.a

LIBS := -lreadline -L $(HOME)/.brew/opt/readline/lib -I $(HOME)/.brew/opt/readline/include -Iincludes

FLAGS := #-g fsanitize=address #-Wextra -Wall -Werror

$(NAME): $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(NAME) $(LIBS)

all:
	make
	./minishell

re:
	rm minishell
	${MAKE}
