/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:40:58 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/21 13:27:41 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_sphere_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "center") == 0)
		flag[0] = ft_getvectfromenv(&SPHERE(form).ctr, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "radius") == 0)
		flag[1] = ft_getdoublefromenv(&SPHERE(form).r, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[2] = ft_getcolfromenv(&SPHERE(form).mat.col, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "diffuse") == 0)
		flag[3] = ft_getdoublefromenv(&SPHERE(form).mat.diffuse, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "specular") == 0)
		flag[4] = ft_getdoublefromenv(&SPHERE(form).mat.specular, \
				ENVSTRUCT(env)->value);
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
	ft_lstaddend(&SCN.forms, ft_newform());
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

double	hit_sphere(t_ray ray, t_forms *form)
{
	t_vec3 oc;
	double a;
	double b;
	double c;
	double delta;

	oc = vect_sub(ray.org, form->sph.ctr);
	a = vect_mult_scale(ray.dir, ray.dir);
	b = 2.0 * vect_mult_scale(ray.dir, oc);
	c = vect_mult_scale(oc, oc) - (form->sph.r * form->sph.r);
	delta = b * b - 4.0 * a * c;
	if (delta <= 0.0)
		return (-1.0);
	return ((-b - sqrt(delta)) / (2.0 * a));
}

t_col			intersec_sphere(t_ray ray, t_list *sph, t_setup *setup)
{
	if (ray.dist >= 0.0)
	{
		FORM(sph)->norm = normal_vect(vect_sub(vect_add(ray.org, vect_scale(ray.dist, ray.dir)), SPHERE(sph).ctr));
		return (diffuse(setup, sph, ray, SPHERE(sph).mat.col));
	}
	return (setup->background);
}
