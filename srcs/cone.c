/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 20:19:17 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 20:05:06 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_cone_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&CONE(form).org, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "direction") == 0)
		flag[1] = ft_getvectfromenv(&CONE(form).dir, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "degres") == 0)
		flag[2] = ft_getdoublefromenv(&CONE(form).theta, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[3] = ft_getcolfromenv(&CONE(form).mat.col, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "diffuse") == 0)
		flag[4] = ft_getdoublefromenv(&CONE(form).mat.diffuse, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "specular") == 0)
		flag[5] = ft_getdoublefromenv(&CONE(form).mat.specular, \
				ENVSTRUCT(env)->value);
	FORM(form)->num_arg++;
}


size_t			ft_cone(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*form;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCONE)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCONE);
	ft_lstaddend(&SCN.forms, ft_newform());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = CON;
	while (FORM(form)->num_arg < NVARCONE && env && (env = env->next))
		ft_cone_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, NVARCONE) != OK)
		return (setup->error = CONE_ERROR);
	CONE(form).dir = normal_vect(CONE(form).dir);
	*list = env;
	return (OK);
}

double	hit_cone(t_ray ray, t_forms *form)
{
	double a;
	double b;
	double k;
	double delta;
	t_vec3 oc;

	k = tan(form->cone.theta / 2);
	k = k * k;
	oc = ft_vec3vop_r(ray.org, form->cone.org, '-');
	a = ft_vec3multscale(ray.dir, ray.dir)
		- (1 + k) * ft_vec3multscale(ray.dir, form->cone.dir) *
		ft_vec3multscale(ray.dir, form->cone.dir);
	b = 2 * (ft_vec3multscale(ray.dir, oc) - (1 + k) *
			ft_vec3multscale(ray.dir, form->cone.dir) *
			ft_vec3multscale(oc, form->cone.dir));
	k = ft_vec3multscale(oc, oc) - (1 + k) *
		ft_vec3multscale(oc, form->cone.dir) *
		ft_vec3multscale(oc, form->cone.dir);
	delta = b * b - 4 * a * k;
	if (delta <= 0.0)
		return (-1.0);
	return ((-b - sqrt(delta)) / (2.0 * a));
}

t_vec3	normal_cone(t_ray ray, t_cone cone)
{
	double height;
	t_vec3 hit;
	t_vec3 oc;
	double k;
	t_vec3 norm;

	hit = vect_add(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'));
	oc = ft_vec3vop_r(hit, cone.org, '-');
	if (ft_vec3multscale(cone.dir, oc) < 0)
		cone.dir = ft_vec3sop_r(cone.dir, -1.0, '*');
	k = 1 / cos(cone.theta / 2.0);
	height = ft_vec3norm(ft_vec3sop_r(oc, k, '*'));
	norm = normal_vect(ft_vec3vop_r(oc, \
				ft_vec3sop_r(cone.dir, height, '*'), '-'));
	return (norm);
}

t_col			intersec_cone(t_ray ray, t_list *con, t_setup *setup)
{
	t_vec3		norm;
	if (ray.dist >= 0.0)
	{
		norm = normal_cone(ray, CONE(con));
		return (diffuse(norm, con, ray, CONE(con).mat.col));
	}
	return (setup->background);
}
