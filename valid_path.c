/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 03:17:50 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/07 03:34:06 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	**ft_visited(char	**map, t_data *map_data)
{
	bool	**visited;
	int		i;

	i = 0;
	visited = ft_calloc((map_data->i - 2) * (map_data->j - 2),
			sizeof(bool *));
	if (!visited)
		ft_print_err(map);
	while (i < (map_data->i - 2) * (map_data->j - 2))
	{
		visited[i] = ft_calloc(1, sizeof(bool));
		if (!visited[i])
		{
			while (i--)
				free(visited[i]);
			free(visited);
			ft_print_err(map);
		}
		++i;
	}
	return (visited);
}

t_node	*ft_newnode(int x, int y)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->x = x;
	node->y = y;
	node->next = NULL;
	return (node);
}

void	ft_enqueue(t_queue *queue, bool **visited, int x, int y)
{
	t_node	*node;

	node = ft_newnode(x, y);
	if (!queue->size)
		queue->front = node;
	if (queue->rear)
		queue->rear->next = node;
	queue->rear = node;
	visited[x][y] = 1;
	++queue->size;
}

void	ft_dequeue(t_queue *queue)
{
	t_node	*tmp_front;

	tmp_front = queue->front;
	queue->front = tmp_front->next;
	free(tmp_front);
	--queue->size;
}

void	ft_isvalid(t_queue *queue, bool **visited, char **map)
{
	int	i;
	int	j;

	i = queue->front->y;
	j = queue->front->x;
	if (map[i + 1][j] != '1' && !visited[j][i + 1])
		ft_enqueue(queue, visited, j, i + 1);
	if (map[i - 1][j] != '1' && !visited[j][i - 1])
		ft_enqueue(queue, visited, j, i - 1);
	if (map[i][j + 1] != '1' && !visited[j + 1][i])
		ft_enqueue(queue, visited, j + 1, i);
	if (map[i][j - 1] != '1' && !visited[j - 1][i])
		ft_enqueue(queue, visited, j - 1, i);
}

void	ft_bfs(char	**map, t_data *map_data)
{
	bool	**visited;
	t_queue	queue[1];
	int		valid_coins;
	int		valid_exit;

	valid_coins = 0;
	valid_exit = 0;
	visited = ft_visited(map, map_data);
	ft_bzero(queue, sizeof(t_queue));
	ft_enqueue(queue, visited, map_data->p_pos[0], map_data->p_pos[1]);
	while (queue->size)
	{
		ft_isvalid(queue, visited, map);
		if (map[queue->front->y][queue->front->x] == 'E')
			valid_exit = 1;
		else if (map[queue->front->y][queue->front->x] == 'C')
			++valid_coins;
		ft_dequeue(queue);
	}
	if (valid_coins != map_data->coin || !valid_exit)
		ft_print_err(map);
}
