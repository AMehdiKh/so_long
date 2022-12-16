/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:31:12 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/16 18:11:13 by ael-khel         ###   ########.fr       */
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
# include <mlx.h>
# include "./ft_printf/ft_printf.h"
# include "./LibFT/libft.h"

#define WINDOW_X 2560
#define WINDOW_Y 1440

# define SP_X 72
# define SP_Y 72

typedef struct s_data
{
	int		x;
	int		y;
	int		player;
	int		coin;
	int		exit;
	int		changed;
	int		p_pos[2];
	char	**map;
}	t_data;

typedef struct s_node
{
	int				x;
	int				y;
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
	void	*ptr;
	void	*win;
	void	*img;
}	t_mlx;

char	**ft_coords(char *map_name);
char	*ft_strjoin_long(char *s1, char *s2);
void	*ft_free_return(void *ptr1, void *ptr2);
void	map_check(char **map, t_data *map_data);
void	ft_count_items(char **map, t_data *map_data);

bool	**ft_visited(char **map, t_data *map_data);
t_node	*ft_newnode(int x, int y, bool **visited, char **map);
void	ft_enqueue(t_queue *queue, char **map, int y, int x);
void	ft_dequeue(t_queue *queue);
void	ft_isvalid(t_queue *queue, char **map);
void	ft_bfs(char	**map, t_data *map_data);

void	ft_print_err(char **map, char *str);
void	ft_clear(void **ptr);

void	ft_mlx(char **map, t_mlx *mlx, t_data *map_data);
void	ft_put_image(char **map, t_mlx *mlx, t_data *map_data);
void	ft_put_sprite(char pixel, t_mlx *mlx, t_data *map_data, int x, int y);

#endif