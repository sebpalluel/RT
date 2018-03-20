#include "../includes/rtv1.h"

double	ft_quadric_derivative_estimate(double b, double c, double d, double x)
{
	double tmp;

	tmp = x * x;
	return (4 * tmp * x + 3 * b * tmp + 2 * c * x + d);
}

double	ft_quadric_estimate(double b, double c, double d, double x)
{
	double tmp;

	tmp = x * x;
	return (tmp * tmp + b * tmp * x + c * tmp + d * x);
}

double	ft_resolve_quadric_n(double b, double c, double d, double e)
{
	double x0;
	int i;

	if (e == 0)
		return (0);
	x0 = 0;
	while (fabs(ft_quadric_derivative_estimate(b, c, d, x0) + e) < 0.000000001)
		x0 += 1;
	i = 0;
	while (fabs(ft_quadric_estimate(b, c, d, x0) + e) > 0.00000001 && ++i < 1000)
		x0 = x0 - ((ft_quadric_estimate(b, c, d, x0) + e) / ft_quadric_derivative_estimate(b, c, d, x0));
//	printf("%f %f\n", x0, ft_quadric_estimate(b, c, d, x0) + e);
//	printf("b, c, d, e, %f, %f, %f, %f\n", b, c, d, e);
//	printf("%lf\n", NAN);
	if (i == 1000)
		return (INFINITY);
	return (x0);
}

double	ft_resolve_quadric(double b, double c, double d, double e)
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
	i = ft_quadric_estimate(b, c, d, -800) + e;
	j = ft_quadric_estimate(b, c, d, 800) + e;
	if (i < 0)
		sgn = -1;
	i = -800;
	j = 800;
	x0 = ((i + j) / 2.0);
	while (fabs(ft_quadric_estimate(b, c, d, x0) + e) > 0.00000001 && count++ < 1000)
	{
		x0 = ft_quadric_estimate(b, c, d, x0) + e;
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

double	ft_resolve_quadric_min(double b, double c, double d, double e)
{
	double r1;
	double r2;

	r1 = ft_resolve_quadric_n(b, c, d, e);
	if (r1 == INFINITY)
	{
		r1 = ft_resolve_quadric(b, c, d, e);
		if (r1 == INFINITY)
		{
	//		printf("%fx^3 + %fx^2 + %fx + %f\n", b, c, d, e);
			return (-1);
		}
	}

	b = b + r1;
	c = c + r1 * b;
	d = d + r1 * c;
	r2 = ft_resolve_cubic_min(1, b, c, d);
//	printf("prout %f\n", ft_2min_pos(r1, r2));

	return (ft_2min_pos(r1, r2));
}