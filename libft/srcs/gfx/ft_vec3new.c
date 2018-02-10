/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newvec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:33:26 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/01 14:55:58 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3		*ft_vec3new(double x, double y, double z)
{
	t_vec3	*vec3;

	if ((vec3 = (t_vec3*)malloc(sizeof(t_vec3))))
	{
		vec3->x = x;
		vec3->y = y;
		vec3->z = z;
	}
	return (vec3);
}
