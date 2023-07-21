NAME := sku

SRC_DIR	:= src

OBJ_D := obj

SRC := $(wildcard src/*/*.c)

MAIN := $(SRC_DIR)/$(NAME).c

OBJS := $(addprefix $(OBJ_D)/, $(notdir $(SRC:.c=.o)))

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

prod: FLAGS += -O3 -flto
prod: MAKE_RULE += prod
prod: re

$(OBJ_D):
	@mkdir $(OBJ_D)
	@echo "\033[32mCreated $(OBJ_D)/ directory!\033[0m"

run: all
	./$(NAME)

$(MAIN):
	@$(CC) $@ -c -o $(MAIN:.c=.o) $(FLAGS) $(HEADERS) $(LIBS)
	@echo "\033[32mCompiled $(NAME).c!\033[0m"

$(NAME): $(OBJ_D) $(SRC) $(MAIN)
	@$(MAKE) -C $(SRC_DIR)/builtins --quiet $(MAKE_RULE)
	@$(MAKE) -C $(SRC_DIR)/env --quiet $(MAKE_RULE)
	@$(MAKE) -C $(SRC_DIR)/executer --quiet $(MAKE_RULE)
	@$(MAKE) -C $(SRC_DIR)/expander --quiet $(MAKE_RULE)
	@$(MAKE) -C $(SRC_DIR)/sk_libc --quiet $(MAKE_RULE)
	@$(MAKE) -C $(SRC_DIR)/sk_printf --quiet $(MAKE_RULE)
	@$(MAKE) -C $(SRC_DIR)/lexer --quiet $(MAKE_RULE)
	@$(MAKE) -C $(SRC_DIR)/parser --quiet $(MAKE_RULE)
	@$(MAKE) -C $(SRC_DIR)/util --quiet $(MAKE_RULE)
	@$(CC) $(OBJS) $(MAIN) -o $(NAME) $(FLAGS) $(HEADERS) $(LIBS)
	@echo "\033[32mCompiled $(NAME)!"
	@echo
	@echo "Done!\033[0m"


clean:
	@rm -rf $(OBJ_D)
	@echo "\033[32mRemoved $(OBJ_D) folder!\033[0m"

fclean:
	@rm -rf $(NAME) $(OBJ_D)
	@echo "\033[32mRemoved $(NAME) and $(OBJ_D) folder!\033[0m"

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
