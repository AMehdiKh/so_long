NAME = so_long

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = so_long.c outils.c

OBJS = ${SRCS:.c=.o}

.PHONY: all clean fclean re
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) libft.a libftprintf.a libgnl.a -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all