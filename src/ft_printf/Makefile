SRC := ft_printf.c ft_number.c

OUT := $(SRC:.c=.o)

FLAGS := -Wall -Werror -Wextra -c -g

all:
	@gcc $(FLAGS) $(SRC) && ar cr libftprintf.a $(OUT)
clean:
	@rm -f $(OUT)
fclean:
	@rm -f $(OUT) libftprintf.a
re:
	@make fclean && make all
bonus:
	@gcc $(FLAGS) $(SRC:.c=_bonus.c) && ar q libftprintf.a $(OUT:.o=_bonus.o)