NAME = so_long

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c map_parse.c valid_path.c outils.c graphics.c sprites.c ft_moves.c

OBJS = ${SRCS:.c=.o}

.PHONY: all clean fclean re
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) libft.a libftprintf.a -fsanitize=address -static-libsan -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -fsanitize=address -c $<

clean:
	rm -f $(OBJS) *.d

fclean: clean
	rm -f $(NAME)

re: fclean all
#-fsanitize=address -static-libsan#