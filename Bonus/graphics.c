/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:15:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/06 17:03:18 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_mlx(t_mlx *mlx)
{
	char	**map;

	map = mlx->map;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx->win = mlx_init(72 * mlx->x, 72 * mlx->y, "Inferno", true);
	if (!mlx->win)
		ft_err(map, "\e[0;31mError: MinilibX initialization failed");
	ft_put_image(mlx);
	mlx_loop_hook(mlx->win, &ft_animation, mlx);
	mlx_key_hook(mlx->win, &ft_moves, mlx);
	mlx_close_hook(mlx->win, &ft_close, mlx);
	mlx_loop(mlx->win);
}

void	ft_animation(void *param)
{
	t_mlx	*mlx;
	int		x;
	int		y;

	mlx = param;
	x = -1;
	// while (++x < mlx->x)
	// {
		ft_torchs(mlx, x, 0);
		ft_torchs(mlx, x, mlx->y);
		usleep(5000);
	// }
	y = -1;
	// while (++y < mlx->y)
	// {
		ft_torchs(mlx, 0, y);
		ft_torchs(mlx, mlx->x, y);
		usleep(5000);
	// }
	printf("hhhhh");
}

void	ft_torchs(t_mlx *mlx, int x, int y)
{
	ft_image_to_window(mlx, "./textures/torch1.png", x, y);
	ft_image_to_window(mlx, "./textures/torch2.png", x, y);
	ft_image_to_window(mlx, "./textures/torch3.png", x, y);
	ft_image_to_window(mlx, "./textures/torch4.png", x, y);
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
			ft_image_to_window(mlx, "./textures/space_grass.png", x, y);
			if (y == 0 || !(mlx->map[y + 1]) || x == 0 || !(mlx->map[y][x + 1]))
				ft_image_to_window(mlx, "./textures/torch.png", x, y);
			else if (mlx->map[y][x] == '1')
				ft_image_to_window(mlx, "./textures/eye.png", x, y);
			else if (mlx->map[y][x] == 'C')
				ft_image_to_window(mlx, "./textures/coin.png", x, y);
			else if (mlx->map[y][x] == 'E')
				ft_exit_sprite(mlx, x, y);
			else if (mlx->map[y][x] == 'P')
			{
				ft_star_sprite(mlx, mlx->s_cord);
				ft_image_to_window(mlx, "./textures/player_right.png", x, y);
			}
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