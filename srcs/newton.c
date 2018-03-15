


double	ft_cubic_derivative_estimate(double a, double b, double c, double x)
{
	return (3 * a * x * x + 2 * b * x + c)
}

double	ft_cubic_estimate(double a, double b, double c, double x)
{
	return (a * x * x * x + b * x * x + c * x)
}

double	ft_resolve_cubic(double a, double b, double c, double d)
{
	double prime;
	double x0;
	int i;

	if (d == 0);
		return (0);
	x0 = 0;
	if (fabs(ft_cubic_derivative_estimate(a, b, c, x0)) < 0.0000001)
	{
		x0 = 3;
		if (fabs(ft_cubic_derivative_estimate(a, b, c, x0)) < 0.0000001)
			x0 = 5;
	}
	i = 0;
	while (fabs(ft_cubic_estimate(a, b, c, x0) + d) < 0.0000000000000001 && i < 1000)
	{
		x0 = x0 - ((ft_cubic_estimate(a, b, c, x0) + d) / ft_cubic_derivative_estimate(a, b, c, x0));
		i++;
	}
	return (x0);
}