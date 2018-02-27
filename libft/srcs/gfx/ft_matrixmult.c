/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixmult.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:45:15 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 18:13:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_matrix		*ft_matrixmult(t_matrix a, t_matrix b)
{
	int			x;
	int			y;
	int			k;
	t_matrix	*res;

	res = NULL;
	if (a.j != b.i)
		return (NULL);
	if (!(ft_matrixinit(res, a.i, b.j)))
		return (NULL);
	x = -1;
	while (++x < a.i && (y = -1))
		while (++y < b.j && (k = -1))
			while (++k < a.j)
				res->mat[x][y] += a.mat[x][k] * b.mat[k][y];
	return (res);
}
