###############################################################################################################
NAME = so_long
###############################################################################################################
CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD -fsanitize=address
###############################################################################################################
M_DIR = Mandatory

SRCS = main.c map_check.c valid_path.c graphics.c sprites.c moves.c outils.c

OBJS = ${SRCS:%.c=$(M_DIR)/%.o}

M_DEP = ${OBJS:.o=.d}
##############################################################################################################
B_DIR = Bonus

BSRCS = main.c map_check.c valid_path.c graphics.c sprites.c moves.c loop_hook.c enemy.c outils.c

BOBJS = ${BSRCS:%.c=$(B_DIR)/%.o}

B_DEP = ${BOBJS:.o=.d}
##############################################################################################################
LIBFT = ./LibFT/libft.a

LIBMLX = ./linux/libmlx42.a

LIBGLFW = ./MLX42/build/libglfw.3.3.dylib
##############################################################################################################
.PHONY: clean
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LIBMLX) -fsanitize=address -static-libasan -fno-omit-frame-pointer -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

bonus: $(LIBFT) $(BOBJS)
	$(CC) $(BOBJS) $(LIBFT) $(LIBMLX) -fsanitize=address -static-libasan -fno-omit-frame-pointer -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)
	@touch $@

$(LIBFT):
	$(MAKE) -C LibFT

sinclude $(M_DEP) $(B_DEP)

clean:
	$(MAKE) fclean -C LibFT
	rm -f $(OBJS) $(BOBJS) $(M_DEP) $(B_DEP) bonus

fclean: clean
	rm -f $(NAME)

re: fclean all