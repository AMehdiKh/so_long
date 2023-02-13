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

BSRCS = main.c map_check.c valid_path.c graphics.c sprites.c moves.c loop.c outils.c

BOBJS = ${BSRCS:%.c=$(B_DIR)/%.o}

B_DEP = ${BOBJS:.o=.d}
##############################################################################################################
LIBFT = ./LibFT/libft.a

PRINTF = ./ft_printf/libftprintf.a

LIBMLX = ./MLX42/build/libmlx42.a

LIBGLFW = ./MLX42/build/libglfw.3.3.dylib
##############################################################################################################
.PHONY: clean
all: $(NAME)

$(NAME): $(OBJS) 
	$(MAKE) -C LibFT
	$(MAKE) -C ft_printf
	$(CC) $(OBJS) $(LIBFT) $(PRINTF) $(LIBMLX) $(LIBGLFW) -fsanitize=address -static-libsan -fno-omit-frame-pointer -o $(NAME)

bonus: $(BOBJS)
	$(MAKE) -C LibFT
	$(MAKE) -C ft_printf
	$(CC) $(BOBJS) $(LIBFT) $(PRINTF) $(LIBMLX) $(LIBGLFW) -fsanitize=address -static-libsan -fno-omit-frame-pointer -o $(NAME)

sinclude $(M_DEP) $(B_DEP)

clean:
	$(MAKE) fclean -C LibFT
	$(MAKE) fclean -C ft_printf
	rm -f $(OBJS) $(BOBJS) $(M_DEP) $(B_DEP) $(LIBFT) $(PRINTF)

fclean: clean
	rm -f $(NAME)

re: fclean all