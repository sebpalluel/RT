/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 16:05:00 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/20 11:47:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

#define PERSISTANCE	0.75
#define FREQUENCY		25.
#define LAYERS			5

double			ft_perlin(t_vec3 vec3, t_gen gen)
{
	double		perlin;
	double		f;
	double		amp;
	int			i;

	perlin = 0;
	f = gen.p_f;
	amp = 1.;
	i = -1;
	while (++i < (int)gen.p_layers)
	{
		perlin += ft_perlin_noise(vec3.x * f + i, vec3.y *
			f + i, vec3.z * f + i) * amp;
		amp *= gen.p_prst;
		f *= 2;
	}
	perlin *= (1 - gen.p_prst) / (1 - amp);
	return (perlin);
}

double			ft_marble(t_vec3 vec3, t_gen gen)
{
	double		perlin;
	double		marble;

	perlin = ft_perlin(vec3, gen);
	marble = sqrt(fabs(sin(2 * M_PI * perlin)));
	return (marble);
}

double			ft_zebra(t_vec3 vec3, t_gen gen)
{
	double		perlin;
	double		amp;
	double		zebra;

	amp = 200.;
	perlin = ft_perlin(vec3, gen);
	zebra = (sin((vec3.x + perlin * amp) * 2 * M_PI / 200.f) + 1) / 2.f;
	return (zebra);
}

double			ft_wood(t_vec3 vec3, t_gen gen)
{
	double		step;
	double		freq;
	double		perlin;
	double		wood;

	perlin = ft_perlin(vec3, gen);
	step = 0.2;
	wood = fmod(perlin, step);
	if (wood > step / 2)
		wood = step - wood;
	freq = (1 - cos(M_PI * wood / (step / 2.0))) / 2.0;
	return (freq);
}

double			ft_cloud(t_vec3 vec3, t_gen gen)
{
	double		cloud;
	double		amp;

	amp = 20.;
	cloud = ft_perlin(vec3, gen);
	cloud = cos(((vec3.x * vec3.y * vec3.z) /
		(vec3.x * 2)) + cloud * amp) / 2. + 0.5;
	return (cloud);
}

double			ft_checker(t_vec3 vec3, t_gen gen)
{
	int			size;

	(void)gen;
	size = 5;
	vec3 = ft_vec3multscale_r(vec3, 100.);
	if (((int)floor(vec3.x / size)
				+ (int)floor(vec3.y / size)) % 2 != 0)
		return (1.);
	else
		return (0.);
}
