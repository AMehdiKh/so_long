/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:35:40 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/11 11:06:53 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_mlx	mlx[1];

	errno = 0;
	ft_bzero(mlx, sizeof(t_mlx));
	ft_check_arg(mlx, ac, av[1]);
	mlx->map = ft_parse(av[1]);
	map_check(mlx);
	ft_bfs(mlx);
	ft_graphics(mlx);
	return (0);
}

void	ft_check_arg(t_mlx *mlx, int ac, char *av)
{
	mlx_t	*win;

	if (ac != 2 || ft_strlen(av) <= 4)
		ft_err(NULL, "\e[0;31mError: More or less than one map entered");
	if (ft_strncmp(av + (ft_strlen(av) - 4), ".der", 4))
		ft_err(NULL, "\e[0;31mError: The map must be in [.der] format");
	win = mlx_init(1, 1, "this is only for fetching monitor size", false);
	if (!win)
		ft_err(NULL, "\e[0;31mError: MLX init for monitor size failed");
	mlx_get_monitor_size(0, &mlx->max_width, &mlx->max_height);
	mlx_terminate(win);
}
