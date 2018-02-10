/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixrotx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:47:16 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 15:26:20 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_matrixrotx(double **mat, double deg)
{
	double	c;
	double	s;

	c = cos(deg);
	s = sin(deg);
	if (mat)
	{
		mat[3][3] = 1;
		mat[0][0] = 1;
		mat[1][1] = c;
		mat[1][2] = -s;
		mat[2][1] = s;
		mat[2][2] = c;
	}
}
