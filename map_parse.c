/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:58:06 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/03 20:13:06 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_parse(char *map_name)
{
	char	**map;
	char	*line;
	int		fd;

	map_name = ft_strjoin("./maps/", map_name);
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
	{
		fd = open(map_name + 7, O_RDONLY);
		if (fd < 0)
		{
			free(map_name);
			ft_print_err(NULL, NULL);
		}
	}
	free(map_name);
	line = ft_line(fd);
	map = ft_split(line, '\n');
	free(line);
	if (!map || !*map)
		ft_print_err(map, "\e[0;31mError: map is empty");
	return (map);
}

char	*ft_line(int fd)
{
	char	*buffer;
	char	*line;
	int		nbyte;

	buffer = ft_calloc(4096, 1);
	line = ft_calloc(1, 1);
	nbyte = 1;
	if (!buffer || !line)
		ft_free_return(line, buffer);
	if (!buffer || !line)
		ft_print_err(NULL, NULL);
	while (nbyte)
	{
		nbyte = read(fd, buffer, 4096);
		if (nbyte < 0)
		{
			ft_free_return(line, buffer);
			ft_print_err(NULL, NULL);
		}
		if (nbyte)
			line = ft_strjoin_long(line, buffer);
	}
	close(fd);
	free(buffer);
	return (line);
}

void	ft_count_items(t_mlx *mlx)
{
	char	**map;

	map = mlx->map;
	if (!ft_strchr("10PCE", map[mlx->y][mlx->x]))
		ft_print_err(map,
			"\e[0;31mError: map composed with invalid characters");
	if (mlx->y == 0 || !(map[mlx->y + 1]) || mlx->x == 0
		|| !(map[mlx->y][mlx->x + 1]))
		if (map[mlx->y][mlx->x] != '1')
			ft_print_err(map,
				"\e[0;31mError: The map is not surrounded by walls");
	if (map[mlx->y][mlx->x] == 'C')
		++mlx->coin;
	else if (map[mlx->y][mlx->x] == 'P')
	{
		mlx->p_cord->y = mlx->y;
		mlx->p_cord->x = mlx->x;
		++mlx->player;
	}
	else if (map[mlx->y][mlx->x] == 'E')
	{
		mlx->e_cord->y = mlx->y;
		mlx->e_cord->x = mlx->x;
		++mlx->exit;
	}
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
				ft_print_err(map, "\e[0;31mError: The map is not rectangular");
	}
	if ((mlx->y * 72) > mlx->max_height || (mlx->x * 72) > mlx->max_width)
		ft_print_err(map, "\e[0;31mError: The map is bigger than monitor size");
	if (mlx->player != 1 || mlx->exit != 1 || mlx->coin < 1)
		ft_print_err(map, "\e[0;31mError: either the map contains a duplicates"
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
