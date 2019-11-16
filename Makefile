CFLAGS =-Wall -Werror -Wextra
NAME = libftprintf.a

SRC_FILE = ft_printf.c\
ft_printf_utils.c\
ft_printf_utils2.c\
ft_printf_makes.c

INC=ft_printf.h
SRC = ${SRC_FILE}
OBJS = ${SRC:.c=.o}

all: ${NAME}

$(NAME): ${OBJS} ${INC}
	ar rcs ${NAME} ${OBJS}
	ranlib ${NAME}

.c.o:  ${SRC} 
	gcc ${CFLAGS} -c -I. $< -o ${<:.c=.o}

clean:
	rm -f ${OBJS} ${BONUS}

fclean: clean
	rm ${NAME}

make bonus : ${BONUS} ${OBJS}
	ar rcs ${NAME} ${OBJS} ${BONUS}
	ranlib ${NAME}

re: clean all
