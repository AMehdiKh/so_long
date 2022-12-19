/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:33:58 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/19 20:57:03 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_right(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y][*x + 1] != '1')
	{
		if (mlx->map[*y][*x + 1] == 'C')
		{
			mlx->map[*y][*x + 1] = '0';
			ft_space_sprite(mlx, (*x + 1), *y);
			--mlx->coin;
		}
		if (mlx->map[*y][*x] != 'E')
			ft_space_sprite(mlx, *x, *y);
		ft_exit_sprite(mlx, mlx->e_pos[1], mlx->e_pos[0]);
		ft_player_sprite(mlx, ++*x, *y);
		mlx->p_pos[1] = *x;
		ft_printf("\033[0;32mThe player move : %d\n", ++mlx->moves);
	}
}

void	ft_left(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y][*x - 1] != '1')
	{
		if (mlx->map[*y][*x - 1] == 'C')
		{
			mlx->map[*y][*x - 1] = '0';
			ft_space_sprite(mlx, (*x - 1), *y);
			--mlx->coin;
		}
		if (mlx->map[*y][*x] != 'E')
			ft_space_sprite(mlx, *x, *y);
		ft_exit_sprite(mlx, mlx->e_pos[1], mlx->e_pos[0]);
		ft_player_sprite(mlx, --*x, *y);
		mlx->p_pos[1] = *x;
		ft_printf("\033[0;32mThe player move : %d\n", ++mlx->moves);
	}
}

void	ft_down(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y + 1][*x] != '1')
	{
		if (mlx->map[*y + 1][*x] == 'C')
		{
			mlx->map[*y + 1][*x] = '0';
			ft_space_sprite(mlx, *x, (*y + 1));
			--mlx->coin;
		}
		if (mlx->map[*y][*x] != 'E')
			ft_space_sprite(mlx, *x, *y);
		ft_exit_sprite(mlx, mlx->e_pos[1], mlx->e_pos[0]);
		ft_player_sprite(mlx, *x, ++*y);
		mlx->p_pos[0] = *y;
		ft_printf("\033[0;32mThe player move : %d\n", ++mlx->moves);
	}
}

void	ft_up(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y - 1][*x] != '1')
	{
		if (mlx->map[*y - 1][*x] == 'C')
		{
			mlx->map[*y + 1][*x] = '0';
			ft_space_sprite(mlx, *x, (*y - 1));
			--mlx->coin;
		}
		if (mlx->map[*y][*x] != 'E')
			ft_space_sprite(mlx, *x, *y);
		ft_exit_sprite(mlx, mlx->e_pos[1], mlx->e_pos[0]);
		ft_player_sprite(mlx, *x, --*y);
		mlx->p_pos[0] = *y;
		ft_printf("\033[0;32mThe player move : %d\n", ++mlx->moves);
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
		won_msg = ft_parse("result_msg.c");
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
