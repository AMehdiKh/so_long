/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 06:37:44 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/02 19:52:49 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_exit_sprite(t_mlx *mlx, int x, int y)
{
	int	size;

	if (mlx->coin)
		mlx->img = mlx_xpm_file_to_image(mlx->ptr,
				"./xpm/closed_door.xpm", &size, &size);
	else
		mlx->img = mlx_xpm_file_to_image(mlx->ptr,
				"./xpm/open_door.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * 72, y * 72);
}

void	ft_space_sprite(t_mlx *mlx, int x, int y)
{
	int	size;

	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/space.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * 72, y * 72);
}

void	ft_in_wall_sprite(t_mlx *mlx, int x, int y)
{
	int	size;

	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/eye.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * 72, y * 72);
}

void	ft_coins_sprite(t_mlx *mlx, int x, int y)
{
	int	size;

	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/coins.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * 72, y * 72);
}

void	ft_player_sprite(t_mlx *mlx, int x, int y)
{
	static int	star_x;
	static int	star_y;
	int			size;

	if (!star_x)
	{
		star_x = mlx->p_pos[1];
		star_y = mlx->p_pos[0];
	}
	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/star.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img,
		star_x * 72, star_y * 72);
	mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/play.xpm", &size, &size);
	mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img, x * 72, y * 72);
}

void	ft_out_wall_sprite(t_mlx *mlx, int x, int y)
{
	int	size;

	if (y == 0 || !(mlx->map[y + 1]) || x == 0
		|| !(mlx->map[y][x + 1]))
	{
		mlx->img = mlx_xpm_file_to_image(mlx->ptr, "./xpm/torch1.xpm",
				&size, &size);
		mlx_put_image_to_window(mlx->ptr, mlx->win, mlx->img,
			x * 72, y * 72);
	}
}
