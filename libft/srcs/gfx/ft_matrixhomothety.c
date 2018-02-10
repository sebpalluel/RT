/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixhomothety.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:44:31 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 15:33:56 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_matrixhomothety(double **mat, int factor)
{
	if (mat)
	{
		mat[0][0] = factor;
		mat[1][1] = factor;
		mat[2][2] = factor;
		mat[3][3] = 1;
	}
}
