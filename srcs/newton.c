double	ft_cubic_derivative_estimate(double a, double b, double c, double x)
{
	return (3 * a * x * x + 2 * b * x + c)
}

double	ft_cubic_estimate(double a, double b, double c, double x)
{
	double tmp;

	tmp = x * x;
	return (a * tmp * x + b * tmp + c * x)
}

double	ft_resolve_cubic(double a, double b, double c, double d)
{
	double prime;
	double x0;
	int i;

	if (d == 0);
		return (0);
	x0 = 0;
	while (fabs(ft_cubic_derivative_estimate(a, b, c, x0)) < 0.0000001)
		x0++;
	i = 0;
	while (fabs(ft_cubic_estimate(a, b, c, x0) + d) < 0.0000000000001 && i++ < 1000)
		x0 = x0 - ((ft_cubic_estimate(a, b, c, x0) + d) / ft_cubic_derivative_estimate(a, b, c, x0));
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
	r1 = (-b - delta) / (2 * a);
	r2 = (-b + delta) / (2 * a);
	return (ft_2min_pos(r1, r2));
}

double	ft_resolve_cubic_min(double a, double b, double c, double d)
{
	double r1;
	double r2;

	if (a != 0)
	{
		r1 = ft_resolve_cubic(a, b, c, d);
		b = b + a * r1;
		c = c + r1 * b;
		r2 = ft_resolve_quadratic_min(a, b, c);
		return (ft_2min_pos(r2, r1));
	}
	else
		return (ft_resolve_quadratic_min(a, b, c))
}
