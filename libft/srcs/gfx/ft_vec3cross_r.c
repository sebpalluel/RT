/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3cross_r.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 16:51:19 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 16:52:50 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3		ft_vec3cross_r(t_vec3 a, t_vec3 b)
{
	t_vec3	to_vec3;

	ft_bzero(&to_vec3, sizeof(t_vec3));
	to_vec3.x = a.y * b.z - a.z * b.y;
	to_vec3.y = a.z * b.x - a.x * b.z;
	to_vec3.z = a.x * b.y - a.y * b.x;
	return (to_vec3);
}
