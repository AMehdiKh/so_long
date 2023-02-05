/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:51:37 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/04 23:16:47 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_free_return(void *ptr1, void *ptr2)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	return (NULL);
}

void	ft_clear(void **ptr)
{
	int	i;

	i = 0;
	if (ptr)
		while (ptr[i])
			++i;
	while (i--)
		free(ptr[i]);
	free(ptr);
}

void	ft_err(char **map, char *str)
{
	if (map)
		ft_clear((void **)map);
	if (errno)
		perror("\e[0;31mError ");
	if (str)
		ft_putendl_fd(str, 2);
	ft_printf("\e[0;32mIt must run like this : ./so_long map_name.der\n");
	exit(EXIT_FAILURE);
}

char	*ft_strjoin_long(char *s1, char *s2)
{
	char	*map_line;
	int		slen;

	slen = ft_strlen(s1) + ft_strlen(s2) + 1;
	map_line = malloc(slen);
	if (!map_line)
	{
		ft_free_return(s1, s2);
		ft_err(NULL, NULL);
	}
	ft_strlcpy(map_line, s1, ft_strlen(s1) + 1);
	ft_strlcat(map_line, s2, slen);
	free(s1);
	return (map_line);
}
