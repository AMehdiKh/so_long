/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 05:08:22 by ael-khel          #+#    #+#             */
/*   Updated: 2023/02/11 06:51:19 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
