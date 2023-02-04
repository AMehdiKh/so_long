/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:35:40 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/04 05:43:55 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_mlx	mlx[1];
	mlx_t	*size;

	errno = 0;
	if (ac != 2 || (ft_strlen(av[1]) <= 4) || ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".der", 4))
		ft_print_err(NULL, "\e[0;31mError: either more/less than one map entered or wrong spelling for the map name");
	size = mlx_init(1, 1, "this is only for fetching window size", false);
	if (!size)
		ft_print_err(NULL, "\e[0;31mError: MinilibX initialization failed");
	ft_bzero(mlx, sizeof(t_mlx));
	mlx_get_monitor_size(0, &mlx->max_width, &mlx->max_height);
	mlx_terminate(size);
	mlx->map = ft_parse(av[1]);
	map_check(mlx);
	ft_bfs(mlx);
	ft_mlx(mlx);
	return (0);
}
//pixlr