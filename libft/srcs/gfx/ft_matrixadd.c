/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixadd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:45:39 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 15:33:05 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_matrixadd(double **mat, double **m, double **n, int size)
{
	int		xy[2];

	if (mat && m && n)
	{
		xy[0] = -1;
		while (++xy[0] < size)
		{
			xy[1] = -1;
			while (++xy[1] < size)
				mat[xy[0]][xy[1]] = m[xy[0]][xy[1]] + n[xy[0]][xy[1]];
		}
	}
}
