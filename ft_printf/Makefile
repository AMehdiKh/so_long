NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_printf.c print_spec.c

OBJS = ${SRCS:.c=.o}

.PHONY: clean
all: $(NAME)

$(NAME): $(OBJS)
	$(AR) rcs $@ $?

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all