/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:15:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/11 08:13:31 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_graphics(t_mlx *mlx)
{
	char	**map;

	map = mlx->map;
	mlx->win = mlx_init(72 * mlx->x, 72 * mlx->y, "Inferno", false);
	if (!mlx->win)
		ft_err(map, "\e[0;31mError: MinilibX initialization failed");
	mlx->img = mlx_new_image(mlx->win, 72 * mlx->x, 72 * mlx->y);
	if (!mlx->img)
	{
		mlx_terminate(mlx->win);
		ft_err(map, "\e[0;31mError: Creating new image failed");
	}
	if (mlx_image_to_window(mlx->win, mlx->img, 0, 0) < 0)
	{
		mlx_delete_image(mlx->win, mlx->img);
		mlx_terminate(mlx->win);
		ft_err(map, "\e[0;31mError: Putting image to window failed");
	}
	ft_put_sprite(mlx);
	mlx_key_hook(mlx->win, &ft_hooks, mlx);
	mlx_close_hook(mlx->win, &ft_close, mlx);
	mlx_loop(mlx->win);
}

void	ft_hooks(mlx_key_data_t keydata, void *param)
{
	t_mlx		*mlx;
	int			x;
	int			y;

	mlx = param;
	x = mlx->p_cord->x;
	y = mlx->p_cord->y;
	if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		mlx->key = keydata.key;
	if (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			ft_up(mlx, &x, &y);
		else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			ft_down(mlx, &x, &y);
		else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			ft_left(mlx, &x, &y);
		else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			ft_right(mlx, &x, &y);
		if ((y == mlx->e_cord->y && x == mlx->e_cord->x && !mlx->coin)
			|| keydata.key == MLX_KEY_ESCAPE)
			ft_esc(mlx, x, y);
	}
}

void	ft_close(void *param)
{
	ft_esc(param, 0, 0);
}
