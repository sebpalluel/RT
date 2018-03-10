/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:34:43 by esuits            #+#    #+#             */
/*   Updated: 2018/02/28 15:20:07 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec3	rand_directed_vec(t_vec3 dir)
{
	t_vec3 ranvect;
	ranvect = ft_vec3_r(rand() * 2.0 - RAND_MAX, 
		rand() * 2.0 - RAND_MAX, 
		rand() * 2.0 - RAND_MAX);
	ranvect = ft_vec3normalize_r(ranvect);
	if (ft_dotproduct(dir, ranvect) < 0)
		ranvect = ft_vec3sop_r(ranvect, -1, '*');
//	printf("%f, %f, %f\n", ranvect.x, ranvect.y, ranvect.z);
	return (ranvect);
}

t_col	global_illum(t_ray ray, t_vec3 norm, t_vec3 origin)
{
	t_ray 	newray;
	int 	i;
	t_setup	*setup;
	t_col	glob;

	setup = get_st();
	glob = setup->background;
	i = 0;
	origin = ft_vec3normalize_r(ft_vec3vop_r(origin, ft_vec3sop_r(norm, 0.00000000001, '*'), '+'));
	newray.org = origin;
	newray.n = ray.n;
	newray.dist = -1;
	newray.nbrefl = ray.nbrefl;
	newray.flag = ray.flag + 1;
	while (i++ <= 100)
	{
		newray.dir = rand_directed_vec(norm);
		glob = ft_coladd(ft_colmultscale(send_ray(newray, setup), 0.01), glob);
	}
//	printf("%f, %f, %f\n", glob.r, glob.g, glob.b);
	return (glob);
}