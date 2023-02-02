/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:58:06 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/02 20:31:19 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_parse(char *map_name, char **map)
{
	t_parse	prs[1];

	if (!(ft_strncmp(map_name + (ft_strlen(map_name) - 4), ".der", 4)))
		map_name = ft_strjoin("./maps/", map_name);
	fd = open(map_name, O_RDONLY);
	free(map_name);
	if (fd < 0)
		ft_print_err(NULL, NULL);
	buffer = ft_calloc(4096, 1);
	map_line = ft_calloc(1, 1);
	if (!buffer || !map_line)
		ft_print_err(NULL, NULL);
	while (read(fd, buffer, 4096))
		map_line = ft_strjoin_long(map_line, buffer);
	close(fd);
	map = ft_split(map_line, '\n');
	ft_free_return(map_line, buffer);
	if (!map || !*map)
		ft_print_err(map, "\033[0;31mError: map is empty");
}

void	ft_count_items(t_mlx *mlx)
{
	char	**map;

	map = mlx->map;
	if (!ft_strchr("10PCE", map[mlx->y][mlx->x]))
		ft_print_err(map,
			"\033[0;31mError: map composed with invalid characters");
	if (mlx->y == 0 || !(map[mlx->y + 1]) || mlx->x == 0
		|| !(map[mlx->y][mlx->x + 1]))
		if (map[mlx->y][mlx->x] != '1')
			ft_print_err(map,
				"\033[0;31mError: The map is not surrounded by walls");
	if (map[mlx->y][mlx->x] == 'P')
	{
		mlx->p_pos[0] = mlx->y;
		mlx->p_pos[1] = mlx->x;
		++mlx->player;
	}
	else if (map[mlx->y][mlx->x] == 'E')
	{
		mlx->e_pos[0] = mlx->y;
		mlx->e_pos[1] = mlx->x;
		++mlx->exit;
	}
	else if (map[mlx->y][mlx->x] == 'C')
		++mlx->coin;
}

void	map_check(t_mlx *mlx)
{
	char	**map;

	map = mlx->map;
	while (map[mlx->y])
	{
		mlx->x = -1;
		while (map[mlx->y][++mlx->x])
			ft_count_items(mlx);
		if (map[++mlx->y])
			if (mlx->x != (int)ft_strlen(map[mlx->y]))
				ft_print_err(map, "\033[0;31mError: The map is not rectangular");
	}
	if (mlx->y * 72 > mlx->max_height || mlx->x * 72 > mlx->max_width)
		ft_print_err(map, "\033[0;31mError: map is longer"
			" than screen resolution");
	if (mlx->player != 1 || mlx->exit != 1 || mlx->coin < 1)
		ft_print_err(map, "\033[0;31mError: either the map contains a duplicates"
			" items (P / E) or contains less than one (C) item");
}

bool	**ft_visited(t_mlx *mlx)
{
	bool	**visited;
	int		i;

	i = 0;
	visited = ft_calloc(mlx->y + 1, sizeof(bool *));
	if (!visited)
		ft_print_err(mlx->map, NULL);
	while (i < mlx->y)
	{
		visited[i] = ft_calloc(mlx->x, sizeof(bool));
		if (!visited[i])
		{
			while (i--)
				free(visited[i]);
			free(visited);
			ft_print_err(mlx->map, NULL);
		}
		++i;
	}
	return (visited);
}
