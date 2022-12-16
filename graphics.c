/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:15:41 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/16 23:21:19 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

void	ft_put_sprite(t_mlx *mlx, t_data *map_data, int x, int y)
{
	ft_space_sprite(mlx, x, y);
	if (map_data->map[y][x] == 'P')
		ft_player_sprite(mlx, map_data, x, y);
	else if (map_data->map[y][x] == '1')
		ft_in_wall_sprite(mlx, x, y);
	else if (map_data->map[y][x] == 'C')
		ft_coins_sprite(mlx, x, y);
	else if (map_data->map[y][x] == 'E')
		ft_exit_sprite(mlx, map_data, x, y);
}

void	ft_exit_sprite(t_mlx *mlx, t_data *map_data, int x, int y)
{
	int	size;

	if (map_data->coin)
		mlx->img = mlx_xpm_file_to_image(mlx->ptr,
				"./xpm/closed_door.xpm", &size, &size);
	else
		mlx->img = mlx_xpm_file_to_image(mlx->ptr,
				"./xpm/open_door.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
}

void	ft_space_sprite(t_mlx *mlx, int x, int y)
{
	int	size;

	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/space.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
}

void	ft_in_wall_sprite(t_mlx *mlx, int x, int y)
{
	int	size;

	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/eye.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
}

void	ft_coins_sprite(t_mlx *mlx, int x, int y)
{
	int	size;

	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/coins.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
}

void	ft_player_sprite(t_mlx *mlx, t_data *map_data, int x, int y)
{
	static int	star_x;
	static int	star_y;
	int			size;

	if (!star_x)
	{
		star_x = map_data->p_pos[1];
		star_y = map_data->p_pos[0];
	}
	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/star.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img,
		star_x * SP_X, star_y * SP_Y);
	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/play.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
}

void	ft_put_image(t_mlx *mlx, t_data *map_data)
{
	int		x;
	int		y;
	char	**map;

	map = map_data->map;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (y == 0 || !(map[y + 1]) || x == 0
				|| !(map[y][x + 1]))
				ft_out_wall_sprite(mlx, map_data, x, y);
			else
				ft_put_sprite(mlx, map_data, x, y);
		}
	}
}

void	ft_out_wall_sprite(t_mlx *mlx, t_data *map_data, int x, int y)
{
	int	size;

	if (y == 0 || !(map_data->map[y + 1]) || x == 0
		|| !(map_data->map[y][x + 1]))
	{
		mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/torch1.xpm",
				&size, &size);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img,
			x * SP_X, y * SP_Y);
	}
}

void	ft_mlx(t_mlx *mlx, t_data *map_data)
{
	char	**map;

	map = map_data->map;
	ft_bzero(mlx, sizeof(t_mlx));
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		ft_print_err(map, "\033[0;31mError: MinilibX initialization failed");
	mlx->win = mlx_new_window(mlx->ptr,
			map_data->x * SP_X, map_data->y * SP_Y, "so_long");
	if (!mlx->win)
	{
		free(mlx->ptr);
		ft_print_err(map, "\033[0;31mError: MinilibX creating window failed");
	}
	ft_put_image(mlx, map_data);
	printf("zbi :%d\n",mlx_key_hook(mlx->win, ft_close, mlx));
	mlx_loop(mlx->ptr);
}

int	ft_close(int keycode, t_mlx *mlx)
{
	if (mlx)
		printf ("%d", keycode);
	// if (keycode == 0)
	// 	mlx_destroy_window(mlx->ptr, mlx->win);
	exit(EXIT_SUCCESS);
	return (0);
}
