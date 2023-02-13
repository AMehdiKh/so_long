/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 02:58:06 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/13 19:18:45 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_check(t_mlx *mlx)
{
	char	**map;

	map = mlx->map;
	while (map[mlx->y])
	{
		mlx->x = -1;
		while (map[mlx->y][++mlx->x])
		{
			if (!ft_strchr("10PCEX", map[mlx->y][mlx->x]))
				ft_err(map, "\e[0;31mError: The map has invalid characters");
			if (mlx->y == 0 || !(map[mlx->y + 1]) || mlx->x == 0
				|| !(map[mlx->y][mlx->x + 1]))
				if (map[mlx->y][mlx->x] != '1')
					ft_err(map, "\e[0;31mError: The map is not surrounded by 1");
			ft_count_items(mlx, mlx->x, mlx->y);
		}
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
		mlx->e_cord->x = x;
		mlx->e_cord->y = y;
		++mlx->exit;
	}
	else if (map[y][x] == 'X')
	{
		mlx->x_cord->x = x;
		mlx->x_cord->y = y;
		++mlx->enemy;
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

int	ft_nbrlen(int n)
{
	int	nbrlen;

	nbrlen = (n == 0);
	while (n)
	{
		++nbrlen;
		n /= 10;
	}
	return (nbrlen);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		nbrlen;

	nbrlen = ft_nbrlen(n);
	str = malloc(nbrlen + 1);
	if (!str)
		return (NULL);
	str[nbrlen--] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[nbrlen--] = (n % 10) + 48;
		n /= 10;
	}
	return (str);
}
