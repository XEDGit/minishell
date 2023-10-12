NAME := sku

SRC_DIR	:= src

OBJ_DIR := obj

SRC := $(wildcard src/*/*.c)

MAIN := $(SRC_DIR)/$(NAME).c

OBJS := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

LIBS := -lreadline -L$(HOME)/.brew/opt/readline/lib

HEADERS := -I$(HOME)/.brew/opt/readline/include -Iincludes

FLAGS := -Wextra -Wall -Werror

all: $(NAME)

debug: MAKE_RULE = debug
debug: $(NAME)

d: FLAGS = -g -fsanitize=address
d: debug

red: fclean d

s: FLAGS = -g
s: debug

res: fclean s

prod: FLAGS += -O3 -flto -Wpedantic
prod: MAKE_RULE += prod
prod: re

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)
	@echo "\033[32mCreated $(OBJ_DIR)/ directory!\033[0m"

run: all
	./$(NAME)

$(MAIN):
	@$(CC) $@ -c -o $(MAIN:.c=.o) $(FLAGS) $(HEADERS) $(LIBS)
	@echo "Compiled \033[32m$(NAME).c!\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/*/%.c | $(OBJ_DIR)
	@$(CC) $< -c -o $@ $(FLAGS) $(HEADERS) $(LIBS)
	@echo "Compiled \033[32m$<.c!\033[0m"

$(NAME): $(OBJS) $(MAIN)
	@$(CC) $(OBJS) $(MAIN) -o $(NAME) $(FLAGS) $(HEADERS) $(LIBS)
	@echo "Linked \033[32m$(NAME)!"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[32mRemoved $(OBJ_DIR) folder!\033[0m"

fclean:
	@rm -rf $(NAME) $(OBJ_DIR)
	@echo "\033[32mRemoved $(NAME) and $(OBJ_DIR) folder!\033[0m"

re: fclean all

mac_lib:
	$(eval LIBS := -lreadline -L/usr/local/opt/readline/lib)
	$(eval HEADERS := -Iincludes -I/usr/local/opt/readline/include)

mac: mac_lib all

m: mac_lib all
	./minishell

mem:
	memdetect  . $(LIBS) $(HEADERS) -e examples -fail $(1)

tester: all
	python3 mstester_2022/tester.py -x ./sku $(1)

.PHONY: all run clean fclean re
