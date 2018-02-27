/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixsop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 14:37:13 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 14:47:04 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		ft_matrixscale(double **mat, int size, double a)
{
	int		xy[2];

	xy[0] = -1;
	while (++xy[0] < size && (xy[1] = -1))
		while (++xy[1] < size)
				mat[xy[0]][xy[1]] *= a;
}
