/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrixtranslate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:43:04 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/09 17:16:44 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_matrixtranslate(double **mat, t_vec3 *vec)
{
	if (mat && vec)
	{
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
		mat[0][3] = vec->x;
		mat[1][3] = vec->y;
		mat[2][3] = vec->z;
	}
}
