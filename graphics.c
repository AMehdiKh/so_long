/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:15:41 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/03 07:43:54 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "man.h"
#include "so_long.h"
#include <stdio.h>

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
			ft_space_sprite(mlx, x, y);
			if (y == 0 || !(mlx->map[y + 1]) || x == 0 || !(mlx->map[y][x + 1]))
				ft_out_wall_sprite(mlx, x, y);
			else if (mlx->map[y][x] == '1')
				ft_in_wall_sprite(mlx, x, y);
			else if (mlx->map[y][x] == 'C')
				ft_coins_sprite(mlx, x, y);
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
	mlx->win = mlx_init(72 * mlx->x, 72 * mlx->y, "So_Long!", false);
	if (!mlx->win)
		ft_print_err(map, "\e[0;31mError: MinilibX initialization failed");
	ft_put_image(mlx);
	mlx_hook(mlx->win, 2, 0, ft_moves, mlx);
	mlx_loop(mlx->win);
	mlx_terminate(mlx->win);
}

int	ft_moves(int keycode, t_mlx *mlx)
{
	int	x;
	int	y;

	x = mlx->p_cord->x;
	y = mlx->p_cord->y;
	if (keycode == RT_ARRW || keycode == D_KEY)
		ft_right(mlx, &x, &y);
	else if (keycode == LT_ARRW || keycode == A_KEY)
		ft_left(mlx, &x, &y);
	else if (keycode == DN_ARRW || keycode == S_KEY)
		ft_down(mlx, &x, &y);
	else if (keycode == UP_ARRW || keycode == W_KEY)
		ft_up(mlx, &x, &y);
	if (keycode == ESC_KEY
		|| ((y == mlx->e_pos[0] && x == mlx->e_pos[1]) && !mlx->coin))
		ft_esc(mlx, x, y);
	return (0);
}
