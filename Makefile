SRC = \
	./srcs/pipex.c \
	./srcs/parsing.c \
	./srcs/pipex_utils.c \
	./srcs/pipex_exec.c \

BONUS = \
	./srcs/bonus/pipex_bonus.c \
	./srcs/bonus/parsing_bonus.c \
	./srcs/bonus/here_doc_bonus.c \
	./srcs/bonus/get_next_line_bonus.c \
	./srcs/bonus/pipex_exec_bonus.c \
	./srcs/bonus/pipex_utils_bonus.c \

OBJ = ${SRC:.c=.o}
BOBJ = ${BONUS:.c=.o}
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

bonus: $(BOBJ)
	make -C $(PRINTF)
	mv $(PRINTF)/libftprintf.a .
	$(CC) $(BOBJ) $(LIBS) -o $(NAME)

clean:
	make clean -C $(PRINTF)
	${RM} ${OBJ}
	${RM} ${BOBJ}

fclean: clean
	make fclean -C $(PRINTF)
	${RM} ./libftprintf.a
	${RM} ${NAME}

re: fclean all

.PHONY : all clean fclean re bonus
