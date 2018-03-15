/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:40:58 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/01 14:42:53 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_sphere_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "center") == 0)
		flag[0] = ft_getvectfromenv(&SPHERE(form).ctr, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "radius") == 0)
		flag[1] = ft_getdoublefromenv(&SPHERE(form).r, ENVSTRUCT(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 2);
	FORM(form)->num_arg++;
}


size_t			ft_sphere(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*form;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARSPHERE)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARSPHERE);
	ft_lstaddend(&SCN.forms, ft_newshape());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = SPH;
	while (FORM(form)->num_arg < NVARSPHERE && env && (env = env->next))
		ft_sphere_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, NVARSPHERE) != OK)
		return (setup->error = SPHERE_ERROR);
	*list = env;
	return (OK);
}

t_vec3			normal_sphere(t_ray ray, t_list *sph)
{
	return (ft_vec3normalize_r(ft_vec3vop_r(ft_vec3vop_r(ray.org, \
						ft_vec3sop_r(ray.dir, ray.dist, '*'), '+'), SPHERE(sph).ctr, '-')));
}

double			hit_sphere(t_ray ray, t_shape *form)
{
	t_vec3		oc;
	double		a;
	double		b;
	double		c;
	double		delta;

	oc = ft_vec3vop_r(ray.org, form->sph.ctr, '-');
	a = ft_vec3dot(ray.dir, ray.dir);
	b = 2.0 * ft_vec3dot(ray.dir, oc);
	c = ft_vec3dot(oc, oc) - (form->sph.r * form->sph.r);
	delta = b * b - 4.0 * a * c;
	if (delta <= 0.0)
		return (-1.0);
	if ((c = (-b - sqrt(delta)) / (2.0 * a)) > 0)
		return (c);
	else
		return ((-b + sqrt(delta)) / (2.0 * a));
}

t_col			intersec_sphere(t_ray ray, t_list *sph, t_setup *setup)
{
	t_vec3		norm;

	if (ray.dist >= 0.0)
	{
		norm = normal_sphere(ray, sph);
		return (diffuse(norm, sph, ray, FORM(sph)->mat));
	}
	return (setup->background);
}
