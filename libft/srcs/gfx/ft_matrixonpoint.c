/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixonpoint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:49:30 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 15:34:19 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_matrixonpoint(double **mat, t_vec3 *vec3)
{
	if (mat && vec3)
	{
		vec3->x = mat[0][0] * vec3->x
			+ mat[0][1] * vec3->y
			+ mat[0][2] * vec3->z + mat[0][3];
		vec3->y = mat[1][0] * vec3->x
			+ mat[1][1] * vec3->y
			+ mat[1][2] * vec3->z + mat[1][3];
		vec3->z = mat[2][0] * vec3->x
			+ mat[2][1] * vec3->y
			+ mat[1][2] * vec3->z + mat[2][3];
	}
}
