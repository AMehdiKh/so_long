/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:33:58 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/19 17:38:09 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_right(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y][*x + 1] != '1')
	{
		if (mlx->map[*y][*x] != 'E')
			ft_space_sprite(mlx, *x, *y);
		ft_exit_sprite(mlx, mlx->e_pos[1], mlx->e_pos[0]);
		if (mlx->map[*y][*x + 1] == 'C' && mlx->coin)
		{
			ft_space_sprite(mlx, (*x + 1), *y);
			--mlx->coin;
		}
		ft_player_sprite(mlx, ++*x, *y);
		mlx->p_pos[1] = *x;
		++mlx->moves;
	}
}

void	ft_left(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y][*x - 1] != '1')
	{
		if (mlx->map[*y][*x] != 'E')
			ft_space_sprite(mlx, *x, *y);
		ft_exit_sprite(mlx, mlx->e_pos[1], mlx->e_pos[0]);
		if (mlx->map[*y][*x - 1] == 'C' && mlx->coin)
		{
			ft_space_sprite(mlx, (*x - 1), *y);
			--mlx->coin;
		}
		ft_player_sprite(mlx, --*x, *y);
		mlx->p_pos[1] = *x;
		++mlx->moves;
	}
}

void	ft_down(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y + 1][*x] != '1')
	{
		if (mlx->map[*y][*x] != 'E')
			ft_space_sprite(mlx, *x, *y);
		ft_exit_sprite(mlx, mlx->e_pos[1], mlx->e_pos[0]);
		if (mlx->map[*y + 1][*x] == 'C' && mlx->coin)
		{
			ft_space_sprite(mlx, *x, (*y + 1));
			--mlx->coin;
		}
		ft_player_sprite(mlx, *x, ++*y);
		mlx->p_pos[0] = *y;
		++mlx->moves;
	}
}

void	ft_up(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y - 1][*x] != '1')
	{
		if (mlx->map[*y][*x] != 'E')
			ft_space_sprite(mlx, *x, *y);
		ft_exit_sprite(mlx, mlx->e_pos[1], mlx->e_pos[0]);
		if (mlx->map[*y - 1][*x] == 'C' && mlx->coin)
		{
			ft_space_sprite(mlx, *x, (*y - 1));
			--mlx->coin;
		}
		ft_player_sprite(mlx, *x, --*y);
		mlx->p_pos[0] = *y;
		++mlx->moves;
	}
}

void	ft_esc(t_mlx *mlx, int x, int y)
{
	char	**won_msg;
	int		i;

	won_msg = NULL;
	if ((y == mlx->e_pos[0] && x == mlx->e_pos[1]) && !mlx->coin)
	{
		i = 12;
		won_msg = ft_coords("result_msg.c");
		while (i < 20)
			ft_printf("\033[0;32m%s\n", won_msg[i++]);
	}
	mlx_destroy_image(mlx->ptr, mlx->img);
	mlx_destroy_window(mlx->ptr, mlx->win);
	ft_clear((void **)mlx->map);
	ft_clear((void **)won_msg);
	free(mlx->ptr);
	exit(EXIT_SUCCESS);
}
