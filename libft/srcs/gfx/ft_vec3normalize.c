/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3normalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:37:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/01 14:56:03 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void		ft_vec3normalize(t_vec3 *to_vec3)
{
	double		sqrt;

	if (to_vec3)
	{
		sqrt = sqrtf(pow(to_vec3->x, 2) + pow(to_vec3->y, 2) + pow(to_vec3->z, 2));
		if (sqrt != 0.)
		{
			to_vec3->x /= sqrt;
			to_vec3->y /= sqrt;
			to_vec3->z /= sqrt;
		}
	}
}
