/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:48:25 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/01 14:55:55 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

double			ft_vec3dist(t_vec3 p1, t_vec3 p2)
{
	double		distance;

	distance = hypot(hypot(p1.x - p2.x, p1.y - p2.y), p1.z - p2.z);
	distance = ABS(distance);
	return (distance);
}
