/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 06:37:44 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/06 16:33:44 by ael-khel         ###   ########.fr       */
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
		ft_err(mlx->map, "\e[0;31mError: Png load failed");
	}
	mlx->img = mlx_texture_to_image(mlx->win, png);
	if (!mlx->img)
	{
		mlx_delete_texture(png);
		mlx_delete_image(mlx->win, mlx->img);
		mlx_terminate(mlx->win);
		ft_err(mlx->map, "\e[0;31mError: Texture to image failed");
	}
	if (mlx_image_to_window(mlx->win, mlx->img, x * 72, y * 72) < 0)
	{
		mlx_delete_texture(png);
		mlx_delete_image(mlx->win, mlx->img);
		mlx_terminate(mlx->win);
		ft_err(mlx->map, "\e[0;31mError: putting image to the window failed");
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

void	ft_star_sprite(t_mlx *mlx, t_cord *s)
{
	ft_image_to_window(mlx, "./textures/star.png", s->x, s->y);
}
