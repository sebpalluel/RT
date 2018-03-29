/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 18:22:54 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/29 18:23:00 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

double	ft_resolve_cubic_n(double a, double b, double c, double d)
{
	double x0;
	int i;

	if (d == 0)
		return (0);
	x0 = 0;
	while (fabs(ft_cubic_derivative_estimate(a, b, c, x0)) < 0.0000001)
		x0 = x0 + 1;
	i = 0;
	while (fabs(ft_cubic_estimate(a, b, c, x0) + d) > 0.00000001 && i++ < 1000)
	{
	//	printf("%f, %f, %d\n", fabs(ft_cubic_estimate(a, b, c, x0) + d), x0, i);
		x0 = x0 - ((ft_cubic_estimate(a, b, c, x0) + d) / ft_cubic_derivative_estimate(a, b, c, x0));
	}
	if (i == 1001)
	{
		//printf("prout\n");
		return (INFINITY);
	}
	return (x0);
}

double	ft_resolve_cubic(double a, double b, double c, double d)
{
	double x0;
	double i;
	double j;
	int count;
	int sgn;

	if (d == 0)
		return (0);
	count = 0;
	sgn = 1;
	i = ft_cubic_estimate(a, b, c, -800) + d;
	j = ft_cubic_estimate(a, b, c, 800) + d;
	if (i < 0)
		sgn = -1;
	i = -800;
	j = 800;
	x0 = ((i + j) / 2.0);
	while (fabs(ft_cubic_estimate(a, b, c, x0) + d) > 0.00000001 && count++ < 1000)
	{
		x0 = ft_cubic_estimate(a, b, c, x0) + d;
		if (sgn * x0 > 0)
			i = (i + j) / 2.0;
		else
			j = (i + j) / 2.0;
		x0 = (i + j) / 2.0;
	}
	if (count == 1001)
		return (INFINITY);
	return (x0);
}

double	ft_resolve_quadratic_min(double a, double b, double c)
{
	double delta;
	double r1;
	double r2;


	delta = b * b - 4 * a * c;
	if (delta <= 0)
		return (-1);
	if (a == 0)
		return (-c / b);
	delta = sqrt(delta);
	r1 = (-b - delta) / (2.0 * a);
	r2 = (-b + delta) / (2.0 * a);
	return (ft_2min_pos(r1, r2));
}

double	ft_resolve_cubic_min(double a, double b, double c, double d)
{
	double r1;
	double r2;

	if (a != 0)
	{
		r1 = ft_resolve_cubic_n(a, b, c, d);
		if (r1 == INFINITY)
		{
			r1 = ft_resolve_cubic(a, b, c, d);
			if (r1 == INFINITY)
			{
		//		printf("%fx^3 + %fx^2 + %fx + %f\n", a, b, c, d);
				return(-1);
			}
		}
		b = b + a * r1;
		c = c + r1 * b;
		r2 = ft_resolve_quadratic_min(a, b, c);
		if (r2 == -1)
			return (r1);
		return (ft_2min_pos(r2, r1));
	}
	else
		return (ft_resolve_quadratic_min(b, c, d));
}
