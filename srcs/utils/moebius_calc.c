/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moebius_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:54:55 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 18:54:56 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static inline double		calc(double x, double ox, double y, double oy)
{
	return (x * x * oy + 2 * x * y * ox);
}

double						moeb_calc1(t_vec3 d)
{
	return (d.x * d.x * d.y + d.y * d.y * d.y - 2 * d.x *
		d.x * d.z - 2 * d.y * d.y * d.z + d.y * d.z * d.z);
}

double						moeb_calc2(t_vec3 d, t_vec3 o, double r)
{
	return (calc(d.x, o.x, d.y, o.y) + 3 * d.y * d.y * o.y
		- 2 * r * d.x * d.z - 2 * calc(d.x, o.x, d.z, o.z) -
		2 * calc(d.y, o.y, d.z, o.z) + calc(d.z, o.z, d.y, o.y));
}

double						moeb_calc3(t_vec3 d, t_vec3 o, double r)
{
	return (-r * r * d.y + 2 * d.x * o.x * o.y
		+ d.y * o.x * o.x + 3 * d.y * o.y * o.y - 2 * r * (o.x * d.z +
		d.x * o.z) - 2 * (2 * d.x * o.x * o.z + d.z * o.x * o.x) - 2 * (2 *
		d.y * o.y * o.z + d.z * o.y * o.y) + 2 * d.z * o.z * o.y + d.y * o.z
			* o.z);
}

double						moeb_calc4(t_vec3 o, double r)
{
	return (-r * r * o.y + o.x * o.x * o.y + o.y * o.y * o.y
		- 2 * r * o.x * o.z - 2 * o.x * o.x * o.z - 2 * o.y * o.y * o.z
		+ o.y * o.z * o.z);
}
