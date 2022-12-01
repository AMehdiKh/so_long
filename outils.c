/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 18:51:37 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/01 01:56:32 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_exit(char *ptr1, char *ptr2)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	exit(EXIT_FAILURE);
}

void	*ft_free_return(char *ptr1, char *ptr2)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	return (NULL);
}

char	*ft_strjoin_long(char *s1, char *s2)
{
	char	*map_line;
	int		slen;

	slen = ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1;
	if (!s2)
		return (s1);
	map_line = malloc(slen);
	if (!map_line)
		ft_free_exit(s1, s2);
	ft_strlcpy(map_line, s1, ft_strlen(s1) + 1);
	ft_strlcat(map_line, s2, slen);
	ft_free_return(s1, s2);
	return (map_line);
}

void	ft_print_err(char **map)
{
	ft_putendl_fd("\033[0;31mError : Map is not valid", 2);
	ft_clear(map);
}

void	ft_clear(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		++i;
	while (i--)
		free(ptr[i]);
	free(ptr);
	exit(EXIT_FAILURE);
}