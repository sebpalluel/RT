/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixroty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:47:59 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 15:34:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_matrixroty(double **mat, double deg)
{
	double	c;
	double	s;

	c = cos(deg);
	s = sin(deg);
	if (mat)
	{
		mat[3][3] = 1;
		mat[0][0] = c;
		mat[0][2] = s;
		mat[1][1] = 1;
		mat[2][0] = -s;
		mat[2][2] = c;
	}
}
