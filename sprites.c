/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 06:37:44 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/04 00:41:02 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	ft_image_to_window(t_mlx *mlx, char *png_path, int x, int y)
{
	mlx_texture_t	*png;

	png = mlx_load_png(png_path);
	if (!png)
	{
		mlx_delete_image(mlx->win, mlx->img);
		mlx_terminate(mlx->win);
		ft_print_err(mlx->map, "\e[0;31mError: 7wa");
	}
	mlx->img = mlx_texture_to_image(mlx->win, png);
	if (!mlx->img)
	{
		mlx_delete_texture(png);
		mlx_delete_image(mlx->win, mlx->img);
		mlx_terminate(mlx->win);
		ft_print_err(mlx->map, "\e[0;31mError: MinilibX 7wa failed");
	}
	if (mlx_image_to_window(mlx->win, mlx->img, x * 72, y * 72) < 0)
	{
		mlx_delete_texture(png);
		mlx_delete_image(mlx->win, mlx->img);
		mlx_terminate(mlx->win);
		ft_print_err(mlx->map, "\e[0;31mError: 7wa initialization failed");
	}
	mlx_delete_texture(png);
}

void	ft_exit_sprite(t_mlx *mlx, int x, int y)
{
	if (mlx->coin)
		ft_image_to_window(mlx, "./textures/d_closed.png", x, y);
	else
		ft_image_to_window(mlx, "./textures/d_open.png", x, y);
}

void	ft_player_sprite(t_mlx *mlx, int x, int y)
{
	static int	star_x;
	static int	star_y;

	if (!star_x)
	{
		star_x = mlx->p_cord->x;
		star_y = mlx->p_cord->x;
	}
	ft_image_to_window(mlx, "./textures/star.png", star_x, star_y);
	ft_image_to_window(mlx, "./textures/player.png", x, y);
}
