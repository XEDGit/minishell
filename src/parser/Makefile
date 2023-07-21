SRCS := $(wildcard *.c)

OBJ_DIR := ../../obj

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

HEADERS := -I$(HOME)/.brew/opt/readline/include -I../../includes

all: $(OBJS)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $< -o $@ -c $(FLAGS) $(HEADERS)
	@echo "\033[32mCompiled $<!\033[0m"

prod: FLAGS = -O3 -flto -Wpedantic
prod: all

debug: FLAGS = -g
debug: all
