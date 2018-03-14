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

	(void)dir;
	ranvect = ft_vec3_r(rand() * 2.0 - RAND_MAX, 
		rand() * 2.0 - RAND_MAX, 
		rand() * 2.0 - RAND_MAX);

	ranvect = ft_vec3normalize_r(ranvect);
	//ranvect = ft_vec3normalize_r(ft_vec3vop_r(ranvect, ft_vec3sop_r(dir, 500, '*'), '+'));
	if (ft_dotproduct(dir, ranvect) < 0)
	{
		ranvect = ft_vec3sop_r(ranvect, -1, '*');
	}
	return (ranvect);
}

t_col	global_illum(t_ray ray, t_vec3 norm, t_vec3 origin, t_list *obj)
{
	t_ray 	newray;
	int 	i;
	t_setup	*setup;
	t_col	glob;
	t_list  *objects;
	double	dist;
	double	olddist;
	(void)obj;

	setup = get_st();

	glob = setup->background;
	i = 0;
	origin = ft_vec3vop_r(origin, ft_vec3sop_r(norm, 0.00000001, '*'), '+');
	newray.org = origin;
	newray.n = ray.n;
	newray.dist = -1;
	newray.nbrefl = ray.nbrefl;
	newray.flag = ray.flag + 1;
	while (i++ <= 100)
	{
		newray.dir = rand_directed_vec(norm);
		olddist = -1;
		objects = setup->scene->forms;
		while (objects)
		{
			if (((dist = hit_shape()[FORM(objects)->type - 1](newray, FORM(objects))) > 0)
				&& ((olddist > dist || olddist == -1)))
				olddist = dist;
			objects = objects->next;
		}
		if (olddist < 0)
			olddist = INFINITY;
		glob = ft_coladd(ft_colmultscale(send_ray(newray, setup), 0.01), glob);
	}

//	printf("%f\n", dist);
//	printf("%f\n", newray.dist);
//	printf("%f, %f, %f\n", glob.r, glob.g, glob.b);
	return (glob);
}

t_col	amb_light(t_col col, t_vec3 norm, t_vec3 dir, double amb_light)
{
	t_col amb;
	double scale;

	scale = fabs(ft_dotproduct(norm, dir));
	scale *= amb_light;
	amb = ft_colmultscale(col, scale);
	return (amb);
}