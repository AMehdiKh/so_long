/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 06:37:44 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/03 07:42:36 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	ft_image_to_window(t_mlx *mlx, char *xpm_path, int x, int y)
{
	xpm_t	*xpm;

	xpm = mlx_load_xpm42(xpm_path);
	if (!xpm)
	{
		mlx_delete_image(mlx->win, mlx->img);
		mlx_terminate(mlx->win);
		ft_print_err(map, "\e[0;31mError: MinilibX initialization failed");
	}
	mlx->img = mlx_texture_to_image(mlx->win, &xpm->texture);
	if (!mlx->img)
	{
		mlx_delete_xpm42(xpm);
		mlx_delete_image(mlx->win, mlx->img);
		mlx_terminate(mlx->win);
		ft_print_err(map, "\e[0;31mError: MinilibX initialization failed");
	}
	if (mlx_image_to_window(mlx->win, mlx->img, x * 72, y * 72) < 0)
	{
		mlx_delete_xpm42(xpm);
		mlx_delete_image(mlx->win, mlx->img);
		mlx_terminate(mlx->win);
		ft_print_err(map, "\e[0;31mError: MinilibX initialization failed");
	}
	mlx_delete_xpm42(xpm);
}

void	ft_exit_sprite(t_mlx *mlx, int x, int y)
{
	if (mlx->coin)
		ft_image_to_window(mlx, "./xpm/closed_door.xpm", x, y);
	else
		ft_image_to_window(mlx, "./xpm/open_door.xpm", x, y);
}

void	ft_space_sprite(t_mlx *mlx, int x, int y)
{
	ft_image_to_window(mlx, "./xpm/space.xpm", x, y);
}

void	ft_in_wall_sprite(t_mlx *mlx, int x, int y)
{
	ft_image_to_window(mlx, "./xpm/eye.xpm", x, y);
}

void	ft_coins_sprite(t_mlx *mlx, int x, int y)
{
	ft_image_to_window(mlx, "./xpm/coins.xpm", x, y);
}

void	ft_player_sprite(t_mlx *mlx, int x, int y)
{
	static int	star_x;
	static int	star_y;

	if (!star_x || !star_y)
	{
		star_x = mlx->p_cord->x;
		star_y = mlx->p_cord->x;
	}
	ft_image_to_window(mlx, "./xpm/star.xpm", star_x, star_y);
	ft_image_to_window(mlx, "./xpm/play.xpm", x, y);
}

void	ft_out_wall_sprite(t_mlx *mlx, int x, int y)
{
	ft_image_to_window(mlx, "./xpm/torch1.xpm", x, y);
}
