NAME := minishell

SRC_DIR	:= src

SRC := builtins/ft_cd.c \
	builtins/ft_echo.c \
	builtins/ft_env.c \
	builtins/ft_exit.c \
	builtins/ft_export.c \
	builtins/ft_pwd.c \
	builtins/ft_unset.c \
	env/buff.c \
	env/env.c \
	env/env_util.c \
	env/setup.c \
	executer/builtins.c \
	executer/exec_utils.c \
	executer/exec_utils2.c \
	executer/executer.c \
	expander/expander.c \
	expander/tilde.c \
	expander/vars.c \
	expander/vars_util.c \
	ft_libc/ft_atoi.c \
	ft_libc/ft_isdigit.c \
	ft_libc/ft_isspace.c \
	ft_libc/ft_itoa.c \
	ft_libc/ft_memset.c \
	ft_libc/ft_split.c \
	ft_libc/ft_strchr.c \
	ft_libc/ft_strcmp.c \
	ft_libc/ft_strdup.c \
	ft_libc/ft_strjoin.c \
	ft_libc/ft_strlcat.c \
	ft_libc/ft_strlcpy.c \
	ft_libc/ft_strlen.c \
	ft_libc/strsplit.c \
	lexer/heredocs.c \
	lexer/lexer.c \
	lexer/syntax_checks.c \
	lexer/syntax_checks2.c \
	lexer/syntax_checks3.c \
	parser/file.c \
	parser/in.c \
	parser/out.c \
	parser/parser.c \
	parser/pipe.c \
	parser/redirect.c \
	util/command.c \
	util/error_handler.c \
	util/pipes.c \
	util/quotes.c \
	util/signal.c \
	minishell.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

LIBS := -lreadline -L$(HOME)/.brew/opt/readline/lib

HEADERS := -I$(HOME)/.brew/opt/readline/include -Iincludes

FLAGS := -g# -Wextra -Wall -Werror #-fsanitize=address 

PRINTF_PATH := src/ft_printf

PRINTF_LIB := $(PRINTF_PATH)/libftprintf.a

all: $(NAME)

run: all
	./$(NAME)

$(NAME): $(PRINTF_LIB) $(SRCS)
	$(CC) $(FLAGS) $^ -o $@ $(LIBS) $(HEADERS)

$(PRINTF_LIB):
	make -C $(PRINTF_PATH)

clean:
	make $@ -C $(PRINTF_PATH)

fclean:
	make $@ -C $(PRINTF_PATH)
	rm -f $(NAME)

re: fclean all

linux_lib:
	$(eval LIBS := -lreadline)
	$(eval HEADERS := -Iincludes -Isrc/ft_printf)

linux: linux_lib all
	./minishell

mac_lib:
	$(eval LIBS := -lreadline -L/usr/local/opt/readline/lib)
	$(eval HEADERS := -Iincludes -I/usr/local/opt/readline/include -Isrc/ft_printf)

m: mac_lib all

mac: mac_lib all
	./minishell

mem:
	memdetect  . $(LIBS) $(HEADERS) -e examples -fail $(1)

tester: all
	python3 new_minishell_tester/tester.py new_minishell_tester/test2 -exe ./minishell $(1)

.PHONY: all run clean fclean re
