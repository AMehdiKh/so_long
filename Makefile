###############################################################################################################
NAME = so_long
###############################################################################################################
CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD
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

LIBMLX = ./MLX42/build/libmlx42.a

LIBGLFW = ./MLX42/build/libglfw.3.3.dylib
##############################################################################################################
.PHONY: clean
all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/ael-khel/goinfre/homebrew/opt/glfw/lib" -o $(NAME)

bonus: $(LIBFT) $(BOBJS)
	$(CC) $(BOBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/ael-khel/goinfre/homebrew/opt/glfw/lib" -o $(NAME)

$(LIBFT):
	@$(MAKE) -C LibFT

sinclude $(M_DEP) $(B_DEP)

clean:
	$(MAKE) fclean -C LibFT
	$(RM) $(OBJS) $(BOBJS) 
	@$(RM) $(M_DEP) $(B_DEP)

fclean: clean
	rm -f $(NAME)

re: fclean all