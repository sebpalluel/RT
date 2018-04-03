/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:34:43 by esuits            #+#    #+#             */
/*   Updated: 2018/04/03 18:07:35 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec3	rand_directed_vec(t_vec3 dir)
{
	t_vec3 ranvect;

	(void)dir;
	ranvect = ft_vec3_r(rand() * 2.0 - RAND_MAX,
		rand() * 2.0 - RAND_MAX,
		rand() * 2.0 - RAND_MAX);
	ranvect = ft_vec3normalize_r(ranvect);
	if (ft_dotproduct(dir, ranvect) < 0)
		ranvect = ft_vec3sop_r(ranvect, -1, '*');
	return (ranvect);
}

t_ray	creat_newray(t_ray ray, t_vec3 norm, t_vec3 org)
{
	t_ray newray;

	newray = ray;
	org = ft_vec3vop_r(org, ft_vec3sop_r(norm, 0.00000001, '*'), '+');
	newray.org = org;
	newray.dist = -1;
	newray.flag += 1;
	return (newray);
}

t_col	global_illum(t_ray ray, t_vec3 norm, t_vec3 origin)
{
	t_ray	newray;
	int		i;
	t_setup	*setup;
	t_col	glob;

	setup = get_st();
	glob = setup->background;
	i = 0;
	newray = creat_newray(ray, norm, origin);
	while (i++ <= 100)
	{
		newray.dir = rand_directed_vec(norm);
		glob = ft_coladd(ft_colmultscale(send_ray(newray, setup), 0.01), glob);
	}
	return (glob);
}

t_col	amb_light(t_col col, t_vec3 norm, t_vec3 dir, double amb_light)
{
	t_col	amb;
	double	scale;

	scale = -ft_dotproduct(norm, dir);
	if (scale <= 0)
		return (ft_colmultscale(col, 0));
	scale *= amb_light;
	amb = ft_colmultscale(col, scale);
	return (amb);
}
