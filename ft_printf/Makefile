SRC = \
	ft_printf.c \
	ft_printf_utils.c \
	ft_printf_unsigned.c \
	ft_puthexa.c \
	ft_ppercent.c \

OBJ = ${SRC:.c=.o}
CC = cc
AR = ar -rcs
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f
NAME = libftprintf.a
LIBFT = "./libft"

all: ${NAME}

%.o: %.c
	$(CC) ${CFLAGS} -c $< -o $@

$(NAME): $(OBJ)
	make bonus -C $(LIBFT)
	cp $(LIBFT)/libft.a $(NAME)
	ar -rcs $(NAME) $(OBJ)

clean:
	make clean -C $(LIBFT)
	${RM} ${OBJ}

fclean: clean
	make fclean -C $(LIBFT)
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re
