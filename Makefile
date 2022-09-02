NAME := minishell

SRC := $(shell find ./src -name '*.c')

LIBS := -lreadline -L$(HOME)/.brew/opt/readline/lib

HEADERS := -I$(HOME)/.brew/opt/readline/include -Iincludes

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
	$(eval HEADERS := -Iincludes -Isrc/ft_printf)

linux: linux_lib all
	./minishell

mac_lib:
	$(eval LIBS := -lreadline -L/usr/local/opt/readline/lib)
	$(eval HEADERS := -Iincludes -I/usr/local/opt/readline/include -Isrc/ft_printf)

mac: mac_lib all
	./minishell

mem:
	memdetect  . $(LIBS) $(HEADERS) -e examples -fail $(1)

tester:
	make
	python3 tester.py