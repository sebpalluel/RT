/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3normalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:37:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/22 11:48:28 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3			ft_vec3normalize_r(t_vec3 from_vec3)
{
	double		sqrt;
	t_vec3		to_vec3;

		sqrt = sqrtf(pow(from_vec3.x, 2) + pow(from_vec3.y, 2) + \
				pow(from_vec3.z, 2));
		ft_bzero(&to_vec3, sizeof(t_vec3));
		if (sqrt != 0.)
		{
			to_vec3.x = from_vec3.x /= sqrt;
			to_vec3.y = from_vec3.y /= sqrt;
			to_vec3.z = from_vec3.z /= sqrt;
		}
		return (to_vec3);
}
