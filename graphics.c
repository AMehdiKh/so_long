/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:15:41 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/16 17:00:44 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_put_sprite(char pixel, t_mlx *mlx, t_data *map_data, int x, int y)
{
	int	size;

	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/space.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
	if (pixel == 'P')
	{
		mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/star.xpm", &size, &size);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
		mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/play.xpm", &size, &size);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
	}
	if (pixel == '1')
	{
		mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/eye.xpm", &size, &size);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
	}
	if (pixel == 'C')
	{
		mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/coins.xpm", &size, &size);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
	}
	if (pixel == 'E')
		ft_exit_sprite(mlx, map_data, x, y);
}

void	ft_exit_sprite(t_mlx *mlx, t_data *map_data, int x, int y)
{
	int	size;

	if (map_data->coin)
		mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/closed_door.xpm", &size, &size);
	else
		mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/open_door.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
}

void	ft_player_sprite(t_mlx *mlx, t_data *map_data, int x, int y)
{
	int	size;
	if (!changed)
	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/star.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/play.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * SP_X, y * SP_Y);
}

void	ft_put_image(char **map, t_mlx *mlx, t_data *map_data)
{
	int	x;
	int	y;
	int	size;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (y == 0 || !(map[y + 1]) || x == 0
				|| !(map[y][x + 1]))
			{
				mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/torch1.xpm",
						&size, &size);
				mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img,
					x * SP_X, y * SP_Y);
			}
			else
				ft_put_sprite(map[y][x], mlx, map_data, x, y);
		}
	}
}

void	ft_mlx(char **map, t_mlx *mlx, t_data *map_data)
{
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
	ft_put_image(map, mlx, map_data);
	mlx_loop(mlx->ptr);
}
