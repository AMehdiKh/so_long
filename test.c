/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 21:42:56 by ael-khel          #+#    #+#             */
/*   Updated: 2022/12/16 21:59:17 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

typedef struct zbi
{
	int	x[1];
}	zbi;

void	ft(zbi *var)
{
	static int	x;

	if (!x)
	x = var->x[0];
	printf ("x = %d, arr = %d\n", x, var->x[0]);
}

int	main(void)
{
	zbi	var[1];

	var->x[0] = 9;
	ft(var);
	var->x[0] += 1;
	ft(var);
	return (0);
}