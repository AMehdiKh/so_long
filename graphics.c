/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:15:41 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/19 20:42:54 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "man.h"
#include "so_long.h"
#include <stdio.h>

void	ft_put_sprite(t_mlx *mlx, int x, int y)
{
	ft_space_sprite(mlx, x, y);
	if (mlx->map[y][x] == 'P')
		ft_player_sprite(mlx, x, y);
	else if (mlx->map[y][x] == '1')
		ft_in_wall_sprite(mlx, x, y);
	else if (mlx->map[y][x] == 'C')
		ft_coins_sprite(mlx, x, y);
	else if (mlx->map[y][x] == 'E')
		ft_exit_sprite(mlx, x, y);
}

void	ft_put_image(t_mlx *mlx)
{
	int		x;
	int		y;
	char	**map;

	map = mlx->map;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (y == 0 || !(map[y + 1]) || x == 0
				|| !(map[y][x + 1]))
				ft_out_wall_sprite(mlx, x, y);
			else
				ft_put_sprite(mlx, x, y);
		}
	}
}

void	ft_mlx(t_mlx *mlx)
{
	char	**map;

	map = mlx->map;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		ft_print_err(map, "\033[0;31mError: MinilibX initialization failed");
	mlx->win = mlx_new_window(mlx->ptr,
			mlx->x * SP_X, mlx->y * SP_Y, "so_long");
	if (!mlx->win)
	{
		free(mlx->ptr);
		ft_print_err(map, "\033[0;31mError: MinilibX creating window failed");
	}
	ft_put_image(mlx);
	mlx_hook(mlx->win, 2, 0, ft_moves, mlx);
	// mlx_loop_hook(mlx->ptr, ft_events, mlx);
	mlx_loop(mlx->ptr);
}

int	ft_moves(int keycode, t_mlx *mlx)
{
	int	y;
	int	x;

	y = mlx->p_pos[0];
	x = mlx->p_pos[1];
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
