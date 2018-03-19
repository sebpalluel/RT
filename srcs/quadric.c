double	ft_quadric_derivative_estimate(double b, double c, double d, double x)
{
	double tmp;

	tmp = x * x;
	return (4 * tmp * x + 3 * b * tmp + 2 * c * x + d)
}

double	ft_quadric_estimate(double b, double c, double d, double x)
{
	double tmp;

	tmp = x * x;
	return (tmp * tmp + b * tmp * x + c * tmp + d * x);
}

double	ft_resolve_quadric(double b, double c, double d, double e)
{
	double prime;
	double x0;
	int i;

	if (e == 0)
		return (0);
	x0 = 0;
	while (fabs(ft_quadric_derivative_estimate(b, c, d, x0) + e) < 0.000000001)
		x0 += 1;
	i = 0;
	while (fabs(ft_quadric_estimate(b, c, d, x0) + e) < 0.00000001 && ++i < 1000)
		x0 = x0 - ((ft_quadric_estimate(b, c, d, x0) + e) / ft_quadric_derivative_estimate(b, c, d, x0));
	if (i == 1000)
		return (SNAN);
	return (x0);
}

double	ft_resolve_quadric_min(double b, double c, double d, double e)
{
	double r1;
	double r2;

	r1 = ft_resolve_quadric(b, c, d, e);
	if (r1 == SNAN)
		return (-1);
	b = b + r1;
	c = c + r1 * b;
	d = d + r1 * c;
	r2 = ft_resolve_cubic_min(1, b, c, d);
	return (ft_2min_pos(r1, r2));
}