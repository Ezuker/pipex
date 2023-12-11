SRC = \
	pipex.c \

OBJ = ${SRC:.c=.o}
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
NAME = pipex
PRINTF = "./ft_printf"
LIBS	= libftprintf.a

all: ${NAME}

%.o: %.c
	$(CC) ${CFLAGS} -c $< -o $@

$(NAME): $(OBJ)
	make -C $(PRINTF)
	mv $(PRINTF)/libftprintf.a .
	$(CC) $(OBJ) $(LIBS) -o $(NAME)

clean:
	make clean -C $(PRINTF)
	${RM} ${OBJ}

fclean: clean
	make fclean -C $(PRINTF)
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re
