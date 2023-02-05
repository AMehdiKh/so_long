###############################################################################################################
NAME = so_long
###############################################################################################################
CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD -fsanitize=address
###############################################################################################################
M_DIR = Mandatory

SRCS = main.c map_check.c valid_path.c outils.c graphics.c sprites.c moves.c

OBJS = ${SRCS:%.c=$(M_DIR)/%.o}

M_DEP = ${OBJS:.o=.d}
##############################################################################################################
B_DIR = Bonus

BSRCS = main.c map_check.c valid_path.c outils.c graphics.c sprites.c moves.c

BOBJS = ${BSRCS:%.c=$(M_DIR)/%.o}

B_DEP = ${BOBJS:.o=.d}
##############################################################################################################
LIBFT = ./LibFT/libft.a

PRINTF = ./ft_printf/libftprintf.a

LIBMLX = /home/amehdikh/MLX42/build/libmlx42.a
##############################################################################################################
.PHONY: clean
all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C LibFT
	$(MAKE) -C ft_printf
	$(CC) $(OBJS) $(LIBFT) $(PRINTF) $(LIBMLX) -fsanitize=address -static-libasan -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

bonus: $(OBJS)
	$(MAKE) -C LibFT
	$(MAKE) -C ft_printf
	$(CC) $(OBJS) $(LIBFT) $(PRINTF) $(LIBMLX) -fsanitize=address -static-libasan -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

sinclude $(M_DEP) $(B_DEP)

clean:
	$(MAKE) fclean -C LibFT
	$(MAKE) fclean -C ft_printf
	rm -f $(OBJS) $(BOBJS) $(M_DEP) $(B_DEP) $(LIBFT) $(PRINTF)

fclean: clean
	rm -f $(NAME)

re: fclean all