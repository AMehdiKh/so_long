/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:15:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/04 05:47:42 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
			ft_image_to_window(mlx, "./textures/space.png", x, y);
			if (y == 0 || !(mlx->map[y + 1]) || x == 0 || !(mlx->map[y][x + 1]))
				ft_image_to_window(mlx, "./textures/torch.png", x, y);
			else if (mlx->map[y][x] == '1')
				ft_image_to_window(mlx, "./textures/eye.png", x, y);
			else if (mlx->map[y][x] == 'C')
				ft_image_to_window(mlx, "./textures/coin.png", x, y);
			else if (mlx->map[y][x] == 'E')
				ft_exit_sprite(mlx, x, y);
			else if (mlx->map[y][x] == 'P')
				ft_player_sprite(mlx, x, y);
		}
	}
}

void	ft_mlx(t_mlx *mlx)
{
	char	**map;

	map = mlx->map;
	mlx->win = mlx_init(72 * mlx->x, 72 * mlx->y, "So_Long!", true);
	if (!mlx->win)
		ft_print_err(map, "\e[0;31mError: MinilibX initialization failed");
	ft_put_image(mlx);
	mlx_loop_hook(mlx->win, &ft_moves, mlx);
	mlx_loop(mlx->win);
}

void	ft_moves(void *param)
{
	t_mlx	*mlx;
	mlx_t	*win;
	int		x;
	int		y;

	mlx = param;
	win = mlx->win;
	x = mlx->p_cord->x;
	y = mlx->p_cord->y;
	if (mlx_is_key_down(win, MLX_KEY_UP) || mlx_is_key_down(win, MLX_KEY_W))
		ft_up(mlx, &x, &y);
	if (mlx_is_key_down(win, MLX_KEY_DOWN)
		|| mlx_is_key_down(win, MLX_KEY_S))
		ft_down(mlx, &x, &y);
	if (mlx_is_key_down(win, MLX_KEY_LEFT)
		|| mlx_is_key_down(win, MLX_KEY_A))
		ft_left(mlx, &x, &y);
	if (mlx_is_key_down(win, MLX_KEY_RIGHT)
		|| mlx_is_key_down(win, MLX_KEY_D))
		ft_right(mlx, &x, &y);
	if ((y == mlx->e_cord->y && x == mlx->e_cord->x && !mlx->coin)
		|| mlx_is_key_down(win, MLX_KEY_ESCAPE))
		ft_esc(mlx, x, y);
}
