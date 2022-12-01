/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:58:06 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/01 02:02:27 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "LibFT/libft.h"
#include "ft_printf/ft_printf.h"
#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_perror_map(void)
{
	int		map_fd;
	char	*str;

	map_fd = open("maps_names.txt", O_RDONLY);
	if (errno)
		perror("\033[0;31mError ");
	else
		ft_putendl_fd("Error : no map or more than one map ", 2);
	ft_printf("\033[0;32mChoose one of the maps listed below :\n\033[0m");
	while (1)
	{
		str = get_next_line(map_fd);
		if (!str)
		{
			ft_printf("\033[0;32mIt must seem like : ./fdf map_name.fdf\n\033[0m");
			close(map_fd);
			exit(EXIT_FAILURE);
		}
		ft_printf("	=> \033[0;33m%s \033[0m", str);
		free (str);
	}
}

char	**ft_coords(int map_fd)
{
	char	*map_line;
	char	*line;

	map_line = ft_calloc(1, 1);
	while (1)
	{
		line = get_next_line(map_fd);
		if (!line)
		{
			close(map_fd);
			return (ft_split(map_line, '\n'));
		}
		map_line = ft_strjoin_long(map_line, line);
	}
}

void	map_parse(char **map, t_data *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr_gnl("10PCE", map[i][j]))
				ft_print_err(map);
			if (i == 0 || !(map[i + 1]) || j == 0 || !(map[i][j + 1]))
				if (map[i][j] != '1')
					ft_print_err(map);
			if (map[i][j] == 'P')
				++map_data->player;
			else if (map[i][j] == 'C')
				++map_data->coin;
			else if (map[i][j] == 'E')
				++map_data->exit;
		}
		if (map[++i])
			if (j != (int)ft_strlen(map[i]))
				ft_print_err(map);
	}
	if (map_data->player != 1 || map_data->exit != 1 || map_data->coin < 1)
		ft_print_err(map);
}

int	main(int ac, char **av)
{
	t_data	map_data[1];
	char	**map;
	char	*str;
	int		map_fd;

	errno = 0;
	if (ac != 2)
		ft_perror_map();
	str = ft_strjoin("./maps/", av[1]);
	map_fd = open(str, O_RDONLY);
	free(str);
	if (map_fd < 0)
		ft_perror_map();
	map = ft_coords(map_fd);
	ft_bzero(map_data, sizeof(t_data));
	map_parse(map, map_data);
	return (0);
}
