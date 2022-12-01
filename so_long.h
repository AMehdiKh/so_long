/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:31:12 by ael-khel          #+#    #+#             */
/*   Updated: 2022/11/30 21:14:00 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

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
# include "./get_next_line/get_next_line.h"

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
	int	player;
	int	space;
	int	wall;
	int	coin;
	int	exit;
}	t_data;

int		ft_perror_maps(void);

char	*ft_strjoin_long(char *s1, char *s2);

char	**ft_coords(int map_fd);

void	*ft_free_return(char *ptr1, char *ptr2);

void	ft_free_exit(char *ptr1, char *ptr2);

void	ft_print_err(char **map);

void	ft_clear(char **ptr);

void	map_parse(char **map, t_data	*map_data);

#endif