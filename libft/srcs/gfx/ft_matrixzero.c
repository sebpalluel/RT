/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixzero.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 19:04:30 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 19:04:38 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		**ft_matrixzero(int size)
{
	double	**mat;
	int		x;
	int		y;

	mat = (double**)malloc(sizeof(double*) * (size + 1));
	if (mat == NULL)
		return (NULL);
	x = -1;
	while (++x < size)
	{
		y = -1;
		mat[x] = (double*)malloc(sizeof(double) * size);
		if (mat[x] == NULL)
			return (NULL);
		while (++y < size)
			mat[x][y] = 0;
	}
	mat[size] = NULL;
	return (mat);
}
