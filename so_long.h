/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:31:12 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/08 18:53:49 by ael-khel         ###   ########.fr       */
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

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

typedef struct s_data
{
	int		x;
	int		y;
	int		player;
	int		coin;
	int		exit;
	int		p_pos[2];
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
void	ft_count_items(t_data *map_data, char item);

bool	**ft_visited(char **map, t_data *map_data);
t_node	*ft_newnode(int x, int y, bool **visited, char **map);
void	ft_enqueue(t_queue *queue, char **map, int y, int x);
void	ft_dequeue(t_queue *queue);
void	ft_isvalid(t_queue *queue, char **map);
void	ft_bfs(char	**map, t_data *map_data);

void	ft_print_err(char **map, char *str);
void	ft_clear(void **ptr);

#endif