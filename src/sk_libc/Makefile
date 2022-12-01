SRCS := $(wildcard *.c)

OBJ_DIR := ../../obj

OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

LIBS := -lreadline -L$(HOME)/.brew/opt/readline/lib

HEADERS := -I$(HOME)/.brew/opt/readline/include -I../../includes

all: $(OBJS)

$(OBJ_DIR)/%.o: %.c
	@$(CC) $< -o $@ -c $(FLAGS) $(HEADERS) $(LIBS)
	@echo "\033[32mCompiled $<!\033[0m"
	$(eval N := $<)
	mv -n $(N) $(subst ft,sk,$(N))

debug: FLAGS = -g
debug: all
