SRC := ft_printf.c ft_number.c

NAME := libftprintf.a

OUT := $(SRC:.c=.o)

FLAGS := -Wall -Werror -Wextra -c -I../../includes

all: $(NAME)

$(NAME): $(OUT)
	ar cr $(NAME) $(OUT)
$(OUT):
	@gcc $(FLAGS) $(SRC)
clean:
	@rm -f $(OUT)
fclean:
	@rm -f $(OUT) $(NAME)
re: fclean all