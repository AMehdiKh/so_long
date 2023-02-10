/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:58:06 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/10 02:45:13 by ael-khel         ###   ########.fr       */
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
			ft_err(NULL, NULL);
		}
	}
	free(map_name);
	line = ft_line(fd);
	map = ft_split(line, '\n');
	free(line);
	if (!map || !*map)
		ft_err(map, "\e[0;31mError: map is empty");
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
		ft_err(NULL, NULL);
	while (nbyte)
	{
		nbyte = read(fd, buffer, 4096);
		if (nbyte < 0)
		{
			ft_free_return(line, buffer);
			ft_err(NULL, NULL);
		}
		buffer[nbyte] = '\0';
		line = ft_strjoin_long(line, buffer);
	}
	close(fd);
	free(buffer);
	return (line);
}

void	map_check(t_mlx *mlx)
{
	char	**map;

	map = mlx->map;
	while (map[mlx->y])
	{
		mlx->x = -1;
		while (map[mlx->y][++mlx->x])
			ft_count_items(mlx, mlx->x, mlx->y);
		if (map[++mlx->y])
			if (mlx->x != (int)ft_strlen(map[mlx->y]))
				ft_err(map, "\e[0;31mError: The map is not rectangular");
	}
	if ((mlx->y * 72) > mlx->max_height || (mlx->x * 72) > mlx->max_width)
		ft_err(map, "\e[0;31mError: The map is bigger than monitor size");
	if (mlx->player != 1 || mlx->exit != 1 || mlx->coin < 1)
		ft_err(map, "\e[0;31mError: The number of items in map is incorrect");
}

void	ft_count_items(t_mlx *mlx, int x, int y)
{
	char	**map;

	map = mlx->map;
	if (!ft_strchr("10PCE", map[y][x]))
		ft_err(map, "\e[0;31mError: The map has invalid characters");
	if (y == 0 || !(map[y + 1]) || x == 0 || !(map[y][x + 1]))
		if (map[y][x] != '1')
			ft_err(map, "\e[0;31mError: The map is not surrounded by 1");
	if (map[y][x] == 'C')
		++mlx->coin;
	else if (map[y][x] == 'P')
	{
		mlx->p_cord->x = x;
		mlx->p_cord->y = y;
		mlx->s_cord->x = x;
		mlx->s_cord->y = y;
		++mlx->player;
	}
	else if (map[y][x] == 'E')
	{
		mlx->e_cord->y = y;
		mlx->e_cord->x = x;
		++mlx->exit;
	}
}

bool	**ft_visited(t_mlx *mlx)
{
	bool	**visited;
	int		i;

	i = 0;
	visited = ft_calloc(mlx->y + 1, sizeof(bool *));
	if (!visited)
		ft_err(mlx->map, NULL);
	while (i < mlx->y)
	{
		visited[i] = ft_calloc(mlx->x, sizeof(bool));
		if (!visited[i])
		{
			while (i--)
				free(visited[i]);
			free(visited);
			ft_err(mlx->map, NULL);
		}
		++i;
	}
	return (visited);
}
