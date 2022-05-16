NAME := minishell

SRC := $(shell find ./src -name '*.c') #src/minishell.c src/util/signal.c src/util/ft_split.c src/util/ft_isspace.c src/lexer/lexer.c

LIBS := -lreadline -L$(HOME)/.brew/opt/readline/lib

HEADERS := -I$(HOME)/.brew/opt/readline/include -Iincludes -Isrc/ft_printf

FLAGS := -g #-fsanitize=address -Wextra -Wall -Werror

PRINTF_PATH := src/ft_printf

PRINTF_LIB := $(PRINTF_PATH)/libftprintf.a

all: $(NAME)

run: all
	./$(NAME)

$(NAME): $(PRINTF_LIB) $(SRC)
	$(CC) $(FLAGS) $^ -o $(NAME) $(LIBS) $(HEADERS)

$(PRINTF_LIB):
	make -C $(PRINTF_PATH)

clean:
	make $@ -C $(PRINTF_PATH)

fclean:
	make $@ -C $(PRINTF_PATH)
	rm -f $(NAME)

re: fclean all

.PHONY: all run clean fclean re

linux_lib:
	$(eval LIBS := -lreadline)
	$(eval HEADERS := -Iincludes)

linux: linux_lib all
	./minishell

mac_lib:
	$(eval LIBS := -lreadline -L/usr/local/opt/readline/lib)
	$(eval HEADERS := -Iincludes -I/usr/local/opt/readline/include)

mac: mac_lib all
	./minishell

malloc_wrapper: fclean
	malloc_wrapper --d . --e examples --flags $(LIBS) $(HEADERS)