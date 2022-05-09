NAME := minishell

SRC := $(shell find ./src -name '*.c') #src/minishell.c src/util/signal.c src/util/ft_split.c src/util/ft_isspace.c src/lexer/lexer.c

LIBS := -lreadline -L$(HOME)/.brew/opt/readline/lib

HEADERS := -I$(HOME)/.brew/opt/readline/include -Iincludes

FLAGS := #-g fsanitize=address #-Wextra -Wall -Werror

PRINTF_PATH := src/ft_printf

PRINTF_LIB := $(PRINTF_PATH)/libftprintf.a

all: $(NAME)

run: all
	./$(NAME)

$(NAME): $(PRINTF_LIB) $(SRC)
	$(CC) $(FLAGS) $(LIBS) $(HEADERS) $^ -o $(NAME)

$(PRINTF_LIB):
	make -C $(PRINTF_PATH)

clean:
	make $@ -C $(PRINTF_PATH)

fclean:
	make $@ -C $(PRINTF_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all run clean fclean re

minishell_linux: $(PRINTF_LIB) $(SRC)
	$(CC) $(FLAGS) -L/usr/include -lreadline -Iincludes $^ -o minishell_linux

linux: minishell_linux
	minishell_linux
