/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchalot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 10:23:01 by nchalot           #+#    #+#             */
/*   Updated: 2018/04/04 10:49:48 by nchalot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double	ft_cubic_derivative_estimate(double a, double b, double c, double x)
{
	return (3 * a * x * x + 2 * b * x + c);
}

double	ft_cubic_estimate(double a, double b, double c, double x)
{
	double tmp;

	tmp = x * x;
	return (a * tmp * x + b * tmp + c * x);
}

void	ft_sort_pos(double *a, double *b, double *c)
{
	double tmp;

	if ((*a > *b && *b > 0) || *a < 0)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
	if ((*b > *c && *c > 0) || *b < 0)
	{
		tmp = *c;
		*c = *b;
		*b = tmp;
	}
	if ((*a > *b && *b > 0) || *a < 0)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

t_vec3	change_base(t_vec3 a, t_vec3 x, t_vec3 y)
{
	t_vec3 tmp;

	tmp = a;
	a.x = ft_vec3dot(tmp, x);
	a.y = ft_vec3dot(tmp, y);
	a.z = ft_vec3dot(tmp, ft_vec3vop_r(x, y, 'c'));
	return (a);
}
