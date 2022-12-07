/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:31:12 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/07 03:38:22 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdbool.h>
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

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	void	*img;
}	t_mlx;

typedef struct s_data
{
	int		i;
	int		j;
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
	t_node	*front;
	t_node	*rear;
	int		size;
}	t_queue;

void	ft_perror_map(char *str);

char	*ft_strjoin_long(char *s1, char *s2);

char	**ft_coords(char *map_name);

void	*ft_free_return(char *ptr1, char *ptr2);

void	ft_free_exit(char *ptr1, char *ptr2);

void	ft_print_err(char **map);

void	*ft_clear(char **ptr);

void	map_check(char **map, t_data *map_data);

void	ft_bfs(char	**map, t_data *map_data);

bool	**ft_visited(char	**map, t_data *map_data);

t_node	*ft_newnode(int x, int y);

void	ft_enqueue(t_queue *queue, bool **visited, int x, int y);

void	ft_dequeue(t_queue *queue);

void	ft_isvalid(t_queue *queue, bool **visited, char **map);

void	ft_count_items(t_data *map_data, char item);

#endif