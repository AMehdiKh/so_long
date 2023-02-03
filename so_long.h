/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:31:12 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/03 05:44:43 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <errno.h>
# include "./MLX42/include/MLX.h"
# include "./ft_printf/ft_printf.h"
# include "./LibFT/libft.h"

# define ESC_KEY 53
# define RT_ARRW 124
# define D_KEY 2
# define LT_ARRW 123
# define A_KEY 0
# define DN_ARRW 125
# define S_KEY 1
# define UP_ARRW 126
# define W_KEY 13

typedef struct s_cord
{
	int	x;
	int	y;
}	t_cord;

typedef struct s_node
{
	t_cord	cord[1];
	struct s_node	*next;
}	t_node;

typedef struct s_queue
{
	t_node		*front;
	t_node		*rear;
	int			size;
	bool		**visited;
}	t_queue;

typedef struct s_mlx
{
	mlx_image_t	*img;
	mlx_t		*win;
	t_cord		p_cord[1];
	t_cord		e_cord[1];
	char		**map;
	int			x;
	int			y;
	int			player;
	int			coin;
	int			exit;
	int			moves;
	int			max_width;
	int			max_height;
}	t_mlx;

char	**ft_parse(char *map_name);
char	*ft_strjoin_long(char *s1, char *s2);
void	*ft_free_return(void *ptr1, void *ptr2);
void	map_check(t_mlx *mlx);
void	ft_count_items(t_mlx *mlx);

bool	**ft_visited(t_mlx *mlx);
t_node	*ft_newnode(int x, int y, t_queue *queue, char **map);
void	ft_enqueue(t_queue *queue, char **map, int y, int x);
void	ft_dequeue(t_queue *queue);
void	ft_isvalid(t_queue *queue, char **map);
void	ft_bfs(t_mlx *mlx);

void	ft_print_err(char **map, char *str);
void	ft_clear(void **ptr);

void	ft_mlx(t_mlx *mlx);
void	ft_put_image(t_mlx *mlx);
void	ft_put_sprite(t_mlx *mlx, int x, int y);

void	ft_exit_sprite(t_mlx *mlx, int x, int y);
void	ft_space_sprite(t_mlx *mlx, int x, int y);
void	ft_in_wall_sprite(t_mlx *mlx, int x, int y);
void	ft_coins_sprite(t_mlx *mlx, int x, int y);
void	ft_player_sprite(t_mlx *mlx, int x, int y);
void	ft_out_wall_sprite(t_mlx *mlx, int x, int y);

void	ft_close(t_mlx *mlx);
int		ft_moves(int keycode, t_mlx *mlx);

void	ft_right(t_mlx *mlx, int *x, int *y);
void	ft_left(t_mlx *mlx, int *x, int *y);
void	ft_down(t_mlx *mlx, int *x, int *y);
void	ft_up(t_mlx *mlx, int *x, int *y);
void	ft_esc(t_mlx *mlx, int x, int y);

#endif