###############################################################################################################
NAME = so_long
###############################################################################################################
CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD
###############################################################################################################
MANDIR = Mandatory

OBJDIR = Mandatory/objs

SRCS = main.c map_check.c valid_path.c graphics.c sprites.c moves.c utils.c

OBJS = ${SRCS:%.c=$(OBJDIR)/%.o}

MANDEP = ${OBJS:.o=.d}
##############################################################################################################
BONDIR = Bonus

BOBJDIR = Bonus/objs

BSRCS = main.c map_check.c valid_path.c graphics.c sprites.c moves.c loop_hook.c enemy.c utils.c

BOBJS = ${BSRCS:%.c=$(BOBJDIR)/%.o}

BONDEP = ${BOBJS:.o=.d}
##############################################################################################################
LIBFT = ./LibFT/libft.a

LIBMLX = /home/amehdikh/Desktop/so_short/MLX42/build/libmlx42.a
##############################################################################################################
.PHONY: clean
all: $(NAME)
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm -o $(NAME)

$(OBJDIR)/%.o: $(MANDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(LIBFT) $(BOBJS)
	$(CC) $(BOBJS) $(LIBFT) $(LIBMLX) -fsanitize=address -static-libasan -fno-omit-frame-pointer -Iinclude -ldl -lglfw -pthread -lm -o $(NAME)

$(BOBJDIR)/%.o: $(BONDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C LibFT

sinclude $(MANDEP) $(BONDEP)

clean:
	$(MAKE) fclean -C LibFT
	$(RM) -r $(OBJDIR) $(BOBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

#$(CC) $(OBJS) $(LIBFT) $(LIBMLX) -Iinclude -lglfw -L"/Users/ael-khel/goinfre/homebrew/opt/glfw/lib" -o $@
#./MLX42/build/libmlx42.a