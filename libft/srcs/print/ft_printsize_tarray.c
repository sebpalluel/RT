/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printsize_tarray.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 18:59:32 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/18 16:43:31 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_printsize_tarray(size_t **map, size_t width, size_t height)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (j > 0)
				ft_putchar(' ');
			if (map[i][j] == 1)
				ft_putstr(ANSI_RED);
			else if (map[i][j] == 2)
				ft_putstr(ANSI_CYAN);
			else
				ft_putstr(ANSI_GREEN);
			ft_putnbr(map[i][j]);
			j++;
		}
		ft_putchar('\n');
		ft_putstr(ANSI_RESET);
		i++;
	}
}
