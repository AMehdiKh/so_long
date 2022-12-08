/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 03:17:50 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/08 16:34:57 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_node	*ft_newnode(int x, int y, bool **visited, char **map)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
	{
		ft_clear((void **)visited);
		ft_print_err(map, NULL);
	}
	node->x = x;
	node->y = y;
	node->next = NULL;
	return (node);
}

void	ft_enqueue(t_queue *queue, char **map, int y, int x)
{
	t_node	*node;

	node = ft_newnode(x, y, queue->visited, map);
	if (!queue->size)
		queue->front = node;
	if (queue->rear)
		queue->rear->next = node;
	queue->rear = node;
	queue->visited[y][x] = true;
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

void	ft_isvalid(t_queue *queue, char **map)
{
	int	x;
	int	y;

	x = queue->front->x;
	y = queue->front->y;
	if (map[y + 1][x] != '1' && !queue->visited[y + 1][x])
		ft_enqueue(queue, map, y + 1, x);
	if (map[y - 1][x] != '1' && !queue->visited[y - 1][x])
		ft_enqueue(queue, map, y - 1, x);
	if (map[y][x + 1] != '1' && !queue->visited[y][x + 1])
		ft_enqueue(queue, map, y, x + 1);
	if (map[y][x - 1] != '1' && !queue->visited[y][x - 1])
		ft_enqueue(queue, map, y, x - 1);
}

void	ft_bfs(char	**map, t_data *map_data)
{
	t_queue	queue[1];
	int		valid_coins;
	int		valid_exit;

	ft_bzero(queue, sizeof(t_queue));
	valid_coins = 0;
	valid_exit = 0;
	queue->visited = ft_visited(map, map_data);
	ft_enqueue(queue, map, map_data->p_pos[0], map_data->p_pos[1]);
	while (queue->size)
	{
		ft_isvalid(queue, map);
		if (map[queue->front->y][queue->front->x] == 'E')
			valid_exit = 1;
		else if (map[queue->front->y][queue->front->x] == 'C')
			++valid_coins;
		ft_dequeue(queue);
	}
	ft_clear((void **)queue->visited);
	if (valid_coins != map_data->coin || !valid_exit)
		ft_print_err(map, "\033[0;31mError: the player in the map has"
			" invalid path, either to the exit or the collectibles or both");
}
