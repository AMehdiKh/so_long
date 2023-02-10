/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:15:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/10 02:09:05 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_mlx(t_mlx *mlx)
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
	ft_put_image(mlx);
	mlx_key_hook(mlx->win, &ft_moves, mlx);
	mlx_close_hook(mlx->win, &ft_close, mlx);
	mlx_loop_hook(mlx->win, &ft_animation, mlx);
	mlx_loop(mlx->win);
}

void	ft_animation(void *param)
{
	t_mlx			*mlx;
	static char		*str[4];
	static int		i;
	static int		j;

	mlx = param;
	if (mlx->coin && j % 7 == 0)
	{
		str[0] = "./textures/torch0.png";
		str[1] = "./textures/torch1.png";
		str[2] = "./textures/torch2.png";
		str[3] = "./textures/torch3.png";
		ft_torches(mlx, str[i++]);
		if (i == 4)
			i = 0;
	}
	if (mlx->coin)
	++j;
	if (!mlx->coin && j)
	{
		ft_torches(mlx, "./textures/torch4.png");
		j = 0;
	}
}

void	ft_torches(t_mlx *mlx, char *str)
{
	int		x;
	int		y;

	x = -1;
	while (++x < mlx->x)
	{
		ft_image_to_window(mlx, str, x, 0);
		ft_image_to_window(mlx, str, x, mlx->y - 1);
	}
	y = -1;
	while (++y < mlx->y)
	{
		ft_image_to_window(mlx, str, 0, y);
		ft_image_to_window(mlx, str, mlx->x - 1, y);
	}
}

void	ft_put_image(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -1;
	while (mlx->map[++y])
	{
		x = -1;
		while (mlx->map[y][++x])
		{
			if (mlx->map[y][x] == '0')
				ft_image_to_window(mlx, "./textures/space_grass.png", x, y);
			else if (mlx->map[y][x] == 'P')
				ft_image_to_window(mlx, "./textures/star_right.png", x, y);
			else if (mlx->map[y][x] == 'E')
				ft_image_to_window(mlx, "./textures/d_closed.png", x, y);
			else if (mlx->map[y][x] == 'C')
				ft_image_to_window(mlx, "./textures/coin.png", x, y);
			else if (mlx->map[y][x] == '1')
				ft_image_to_window(mlx, "./textures/eye.png", x, y);
		}
	}
}

void	ft_moves(mlx_key_data_t keydata, void *param)
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
