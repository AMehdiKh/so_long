/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:58:06 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/16 19:50:35 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		ft_print_err(NULL, NULL);
	one_line = ft_calloc(4096, 1);
	map_line = ft_calloc(1, 1);
	if (!one_line || !map_line)
		ft_print_err(NULL, NULL);
	while (read(fd, one_line, 4096))
		map_line = ft_strjoin_long(map_line, one_line);
	close(fd);
	map = ft_split(map_line, '\n');
	ft_free_return(map_line, one_line);
	if (!map || !*map)
		ft_print_err(map, "\033[0;31mError: map is empty");
	return (map);
}

void	ft_count_items(t_data *map_data)
{
	char	**map;

	map = map_data->map;
	if (!ft_strchr("10PCE", map[map_data->y][map_data->x]))
		ft_print_err(map,
			"\033[0;31mError: map composed with invalid characters");
	if (map_data->y == 0 || !(map[map_data->y + 1]) || map_data->x == 0
		|| !(map[map_data->y][map_data->x + 1]))
		if (map[map_data->y][map_data->x] != '1')
			ft_print_err(map,
				"\033[0;31mError: The map is not surrounded by walls");
	if (map[map_data->y][map_data->x] == 'P')
	{
		map_data->p_pos[0] = map_data->y;
		map_data->p_pos[1] = map_data->x;
		++map_data->player;
	}
	else if (map[map_data->y][map_data->x] == 'C')
		++map_data->coin;
	else if (map[map_data->y][map_data->x] == 'E')
		++map_data->exit;
}

void	map_check(t_data *map_data)
{
	char	**map;

	map = map_data->map;
	while (map[map_data->y])
	{
		map_data->x = -1;
		while (map[map_data->y][++map_data->x])
			ft_count_items(map_data);
		if (map[++map_data->y])
			if (map_data->x != (int)ft_strlen(map[map_data->y]))
				ft_print_err(map, "\033[0;31mError: The map is not rectangular");
	}
	if (map_data->y * SP_Y > WINDOW_Y || map_data->x * SP_X > WINDOW_X)
		ft_print_err(map, "\033[0;31mError: map is longer"
			" than screen resolution");
	if (map_data->player != 1 || map_data->exit != 1 || map_data->coin < 1)
		ft_print_err(map, "\033[0;31mError: either the map contains a duplicates"
			" items (P / E) or contains less than one (C) item");
}

bool	**ft_visited(t_data *map_data)
{
	bool	**visited;
	int		i;

	i = 0;
	visited = ft_calloc(map_data->y + 1, sizeof(bool *));
	if (!visited)
		ft_print_err(map_data->map, NULL);
	while (i < map_data->y)
	{
		visited[i] = ft_calloc(map_data->x, sizeof(bool));
		if (!visited[i])
		{
			while (i--)
				free(visited[i]);
			free(visited);
			ft_print_err(map_data->map, NULL);
		}
		++i;
	}
	return (visited);
}
