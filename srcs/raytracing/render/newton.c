/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nchalot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 10:23:01 by nchalot           #+#    #+#             */
/*   Updated: 2018/04/04 10:23:21 by nchalot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double	ft_resolve_cubic_n(double a, double b, double c, double d)
{
	double	x0;
	int		i;

	if (d == 0)
		return (0);
	x0 = 0;
	while (fabs(ft_cubic_derivative_estimate(a, b, c, x0)) < 0.0000000000001)
		x0 = x0 + 1;
	i = 0;
	while (fabs(ft_cubic_estimate(a, b, c, x0) + d) >
		0.0000000001 && i++ < 1000)
		x0 = x0 - ((ft_cubic_estimate(a, b, c, x0) + d) /
			ft_cubic_derivative_estimate(a, b, c, x0));
	if (i == 1001)
		return (INFINITY);
	return (x0);
}

double	ft_resolve_cubic(double a, double b, double c, double d)
{
	double	x0;
	double	i;
	double	j;
	int		count;
	int		sgn;

	count = 0;
	sgn = 1;
	if (ft_cubic_estimate(a, b, c, -800) + d < 0)
		sgn = -1;
	i = -800;
	j = 800;
	x0 = ((i + j) / 2.0);
	while (fabs(ft_cubic_estimate(a, b, c, x0) + d) >
		0.00000001 && count++ < 1000)
	{
		x0 = ft_cubic_estimate(a, b, c, x0) + d;
		(sgn * x0) > 0 ? (i = (i + j) / 2.0) :
			(j = (i + j) / 2.0);
		x0 = (i + j) / 2.0;
	}
	if (count == 1001)
		return (INFINITY);
	return (x0);
}

int		ft_resolve_quadratic_min(double *a, double *b, double c)
{
	double delta;
	double r1;
	double r2;

	delta = *b * *b - 4 * *a * c;
	if (delta <= 0)
		return (0);
	if (*a == 0)
	{
		*a = -c / *b;
		*b = -1;
		return (1);
	}
	delta = sqrt(delta);
	r1 = (-*b - delta) / (2.0 * *a);
	r2 = (-*b + delta) / (2.0 * *a);
	*a = r1;
	*b = r2;
	return (1);
}

int		ft_resolve_cubic_min(double *a, double *b, double *c, double d)
{
	double r1;
	double r2;

	if (a != 0)
	{
		r1 = ft_resolve_cubic_n(*a, *b, *c, d);
		if (r1 == INFINITY)
		{
			r1 = ft_resolve_cubic(*a, *b, *c, d);
			if (r1 == INFINITY)
				return (0);
		}
		*b = *b + *a * r1;
		*c = *c + r1 * *b;
		r2 = ft_resolve_quadratic_min(a, b, *c);
		*c = r1;
		return (1);
	}
	else
		return (ft_resolve_quadratic_min(b, c, d));
}
