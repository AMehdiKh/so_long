/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:33:58 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/06 14:20:36 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_right(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y][*x + 1] == '1')
		return ;
	if (mlx->map[*y][*x + 1] == 'C')
	{
		ft_image_to_window(mlx, "./textures/space_grass.png", *x + 1, *y);
		mlx->map[*y][*x + 1] = '0';
		--mlx->coin;
	}
	if (mlx->map[*y][*x] != 'E')
		ft_image_to_window(mlx, "./textures/space_grass.png", *x, *y);
	ft_exit_sprite(mlx, mlx->e_cord->x, mlx->e_cord->y);
	ft_star_sprite(mlx, mlx->s_cord);
	ft_image_to_window(mlx, "./textures/player_right.png", ++*x, *y);
	mlx->p_cord->x = *x;
	ft_printf("\e[0;32mThe player move : %d\n", ++mlx->moves);
}

void	ft_left(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y][*x - 1] == '1')
		return ;
	if (mlx->map[*y][*x - 1] == 'C')
	{
		ft_image_to_window(mlx, "./textures/space_grass.png", *x - 1, *y);
		mlx->map[*y][*x - 1] = '0';
		--mlx->coin;
	}
	if (mlx->map[*y][*x] != 'E')
		ft_image_to_window(mlx, "./textures/space_grass.png", *x, *y);
	ft_exit_sprite(mlx, mlx->e_cord->x, mlx->e_cord->y);
	ft_star_sprite(mlx, mlx->s_cord);
	ft_image_to_window(mlx, "./textures/player_left.png", --*x, *y);
	mlx->p_cord->x = *x;
	ft_printf("\e[0;32mThe player move : %d\n", ++mlx->moves);
}


void	ft_down(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y + 1][*x] == '1')
		return ;
	if (mlx->map[*y + 1][*x] == 'C')
	{
		ft_image_to_window(mlx, "./textures/space_grass.png", *x, *y + 1);
		mlx->map[*y + 1][*x] = '0';
		--mlx->coin;
	}
	if (mlx->map[*y][*x] != 'E')
		ft_image_to_window(mlx, "./textures/space_grass.png", *x, *y);
	ft_exit_sprite(mlx, mlx->e_cord->x, mlx->e_cord->y);
	ft_star_sprite(mlx, mlx->s_cord);
	if (mlx->key == MLX_KEY_RIGHT)
		ft_image_to_window(mlx, "./textures/player_right.png", *x, ++*y);
	else
		ft_image_to_window(mlx, "./textures/player_left.png", *x, ++*y);
	mlx->p_cord->y = *y;
	ft_printf("\e[0;32mThe player move : %d\n", ++mlx->moves);
}

void	ft_up(t_mlx *mlx, int *x, int *y)
{
	if (mlx->map[*y - 1][*x] == '1')
		return ;
	if (mlx->map[*y - 1][*x] == 'C')
	{
		mlx->map[*y + 1][*x] = '0';
		ft_image_to_window(mlx, "./textures/space_grass.png", *x, *y - 1);
		--mlx->coin;
	}
	if (mlx->map[*y][*x] != 'E')
		ft_image_to_window(mlx, "./textures/space_grass.png", *x, *y);
	ft_exit_sprite(mlx, mlx->e_cord->x, mlx->e_cord->y);
	ft_star_sprite(mlx, mlx->s_cord);
	if (mlx->key == MLX_KEY_RIGHT)
		ft_image_to_window(mlx, "./textures/player_right.png", *x, --*y);
	else
		ft_image_to_window(mlx, "./textures/player_left.png", *x, --*y);
	mlx->p_cord->y = *y;
	ft_printf("\e[0;32mThe player move : %d\n", ++mlx->moves);
}

void	ft_esc(t_mlx *mlx, int x, int y)
{
	char	**win_msg;
	int		i;

	win_msg = NULL;
	if ((y == mlx->e_cord->y && x == mlx->e_cord->x) && !mlx->coin)
	{
		i = 12;
		win_msg = ft_parse("Mandatory/win_msg.c");
		while (i < 20)
			ft_printf("\e[0;32m%s\n", win_msg[i++]);
	}
	mlx_delete_image(mlx->win, mlx->img);
	mlx_terminate(mlx->win);
	ft_clear((void **)mlx->map);
	ft_clear((void **)win_msg);
	exit(EXIT_SUCCESS);
}
