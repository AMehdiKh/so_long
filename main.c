/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 07:35:40 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/16 18:15:25 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int ac, char **av)
{
	t_data	map_data[1];
	t_mlx	mlx[1];
	char	**map;

	errno = 0;
	if (ac != 2 || (ft_strlen(av[1]) <= 4)
		|| ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".der", 4))
		ft_print_err(NULL, "\033[0;31mError: either more/less than one"
			" map entered or wrong spelling for the map name");
	ft_bzero(map_data, sizeof(t_data));
	map_data->map = ft_coords(av[1]);
	map_check(map_data);
	ft_bfs(map, map_data);
	ft_mlx(map, mlx, map_data);
	return (0);
}
