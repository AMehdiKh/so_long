/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:58:06 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/07 03:17:07 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_perror_map(char *str)
{
	if (errno)
		perror("\033[0;31mError ");
	else
		ft_putendl_fd(str, 2);
	ft_printf("\033[0;32mIt must seem like : ./so_long map_name.der\n");
	exit(EXIT_FAILURE);
}

char	**ft_coords(char *map_name)
{
	char	**map;
	char	*map_line;
	char	*one_line;
	char	*file_path;
	int		fd;

	file_path = ft_strjoin("./maps/", map_name);
	fd = open(file_path, O_RDONLY);
	free(file_path);
	if (fd < 0)
		ft_perror_map(NULL);
	one_line = ft_calloc(4096, 1);
	map_line = ft_calloc(1, 1);
	if (!one_line || !map_line)
		ft_perror_map(NULL);
	while (read(fd, one_line, 4096))
		map_line = ft_strjoin_long(map_line, one_line);
	close(fd);
	map = ft_split(map_line, '\n');
	ft_free_return(map_line, one_line);
	return (map);
}

void	ft_count_items(t_data *map_data, char item)
{
	if (item == 'P')
	{
		map_data->p_pos[0] = map_data->j;
		map_data->p_pos[1] = map_data->i;
		++map_data->player;
	}
	else if (item == 'C')
		++map_data->coin;
	else if (item == 'E')
		++map_data->exit;
}

void	map_check(char **map, t_data *map_data)
{
	while (map[map_data->i])
	{
		map_data->j = -1;
		while (map[map_data->i][++map_data->j])
		{
			if (!ft_strchr("10PCE", map[map_data->i][map_data->j]))
				ft_print_err(map);
			if (map_data->i == 0 || !(map[map_data->i + 1]) || map_data->j == 0
				|| !(map[map_data->i][map_data->j + 1]))
				if (map[map_data->i][map_data->j] != '1')
					ft_print_err(map);
			ft_count_items(map_data, map[map_data->i][map_data->j]);
		}
		if (map[++map_data->i])
			if (map_data->j != (int)ft_strlen(map[map_data->i]))
				ft_print_err(map);
	}
	if (map_data->player != 1 || map_data->exit != 1 || map_data->coin < 1)
		ft_print_err(map);
}

int	main(int ac, char **av)
{
	t_data	map_data[1];
	char	**map;

	errno = 0;
	if (ac != 2 || (ft_strlen(av[1]) <= 4)
		|| ft_strncmp(&av[1][ft_strlen(av[1]) - 4], ".der", 4))
		ft_perror_map("\033[0;31mError : no map or more than one map");
	map = ft_coords(av[1]);
	ft_bzero(map_data, sizeof(t_data));
	map_check(map, map_data);
	ft_bfs(map, map_data);
	return (0);
}
