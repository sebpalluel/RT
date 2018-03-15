static inline double	calc(double x, double ox, double y, double oy)
{
	return (x * x * oy + 2 x * y * ox);
}

static inline double	ft_2min_pos(double a, double b)
{
	if (a < b && a > 0)
		return (a)
	else
		return (b);
}

static inline double	ft_3min_pos(double a, double b, double c)
{
	return (ft_2min_pos(ft_2min_pos(a, b), ft_2min_pos(b, c)));
}

double			hit_moebius(t_ray, t_shape *shape)
{
	t_vec3		oc;
	double 	a;
	double	b;
	double 	c;
	double	d;
	double	r[3];
// verifier avant que notre rayon intersecte une boule de rayon R et pas une boule de rayon r
	t_vec3	d;
	t_vec3	o;
	o = ft_vec3vop_r(ray.org, form->moeb.ctr, '-')
	d.x = form->moeb.dir.x;
	d.y = form->moeb.dir.y;
	d.z = form->moeb.dir.z;

	a = d.x * d.x * d.y + d.y * d.y * d.y - 2 * d.x * d.x * d.z - 2 * d.y * d.y * d.z + d.y * d.z * d.z;
	b = calc(d.x, o.x, d.y, o.y) + 3 * d.y * d.y * o.y - 2 * form->moeb.r * d.x * d.y - 2 * calc(d.x, o.x, d.z, o.z) - 2 * calc(d.y, o.y, d.z, o.z) + calc(d.z, o.z, d.y, o.y);
	c = -form->moeb.r * form->moeb.r * d.y + 2 * d.x * o.x * o.y + d.y * o.x * o.x + 3 * d.y * o.y * o.y - 2 * form->moeb.r * (o.x * d.y + d.x * o.y) - 2 * (2 * d.x * o.x * o.z + d.z * o.x * o.x) - 2 * (2 * d.y * o.y * o.z + d.z * o.y * o.y) + 2 * d.z * o.z * o.y + d.y * o.z * o.z;
	d = -form->moeb.r * form->moeb.r * o.y + o.x * o.x * o.y + o.y * o.y * o.y - 2 * form->moeb.r * o.x * o.y - 2 * o.x * o.x * o.z - 2 * o.y * o.y * o.z  + o.y * o.z * o.z;

	if (a != 0)
	{
		r[0] = ft_resolve_cubic(a, b, c, d);
		b = (b - r * a);
		c = c - r * b;
		r[1] = ft_resolve_quadric(a, b, c, 0);
		if (r[1] != SNAN)
			r[2] = ft_resolve_quadric(a, b, c, 1);
		else
			return (r[0]);
		return (ft_3min_pos(r[0], r[1], r[2]));
	}
	else
	{
		r[0] = ft_resolve_quadric(b, c, d, 0);
		if (r[0] != SNAN)
			r[1] = ft_resolve_quadric(a, b, c, 1);
		else
			return (-1.0);
		return (ft_2min_pos(r[0], r[1]));
	}
}