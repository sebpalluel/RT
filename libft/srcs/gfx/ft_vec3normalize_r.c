/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3normalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:37:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/22 15:40:16 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3			ft_vec3normalize_r(t_vec3 from_vec3)
{
	double		sqrt;
	t_vec3		to_vec3;

	if ((sqrt = sqrtf(pow(from_vec3.x, 2) + pow(from_vec3.y, 2) + \
					pow(from_vec3.z, 2))) <= 0.)
		return (ft_vec3_r(0., 0., 0.));
	to_vec3.x = from_vec3.x / sqrt;
	to_vec3.y = from_vec3.y / sqrt;
	to_vec3.z = from_vec3.z / sqrt;
	return (to_vec3);
}
