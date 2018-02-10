/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixrotz.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:48:41 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 15:34:45 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_matrixrotz(double **mat, double deg)
{
	double	c;
	double	s;

	c = cos(deg);
	s = sin(deg);
	if (mat)
	{
		mat[3][3] = 1;
		mat[2][2] = 1;
		mat[0][0] = c;
		mat[0][1] = -s;
		mat[1][0] = s;
		mat[1][1] = c;
	}
}
