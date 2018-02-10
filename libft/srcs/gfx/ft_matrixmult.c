/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixmult.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:45:15 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 15:34:07 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_matrixmult(double **mat, double **m, double **n, int size)
{
	double	temp;
	int		xyz[3];

	if (mat && m && n)
	{
		xyz[0] = -1;
		while (++xyz[0] < size)
		{
			xyz[1] = -1;
			while (++xyz[1] < size)
			{
				temp = 0;
				xyz[2] = -1;
				while (++xyz[2] < size)
					temp = temp + m[xyz[0]][xyz[2]] * n[xyz[2]][xyz[1]];
				mat[xyz[0]][xyz[1]] = temp;
			}
		}
	}
}
