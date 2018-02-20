/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/20 19:00:27 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_plane_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "normale") == 0)
		flag[0] = ft_getvectfromenv(&PLAN(form).nrml, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "distance") == 0)
		flag[1] = ft_getdoublefromenv(&PLAN(form).dst, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[2] = ft_getcolfromenv(&PLAN(form).mat.col, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "diffuse") == 0)
		flag[3] = ft_getdoublefromenv(&PLAN(form).mat.diffuse, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "specular") == 0)
		flag[4] = ft_getdoublefromenv(&PLAN(form).mat.specular, \
				ENVSTRUCT(env)->value);
	FORM(form)->num_arg++;
}

size_t			ft_plane(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*form;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARPLANE)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARPLANE);
	ft_lstaddend(&SCN.forms, ft_newform());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = PLN;
	while (FORM(form)->num_arg < NVARPLANE && env && (env = env->next))
		ft_plane_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, NVARPLANE) != OK)
		return (setup->error = PLANE_ERROR);
	PLAN(form).nrml = normal_vect(PLAN(form).nrml);
	*list = env;
	return (OK);
}

double	hit_plan(t_ray ray, t_forms *form)
{
	double a;
	double b;

	a = vect_mult_scale(ray.dir, form->plan.nrml);
	if (a == 0)
		return (-1);
	b = vect_mult_scale(form->plan.nrml, vect_add(ray.org,
				vect_scale(form->plan.dst, form->plan.nrml)));
	return (-b / a);
	}

t_col			intersec_plan(t_ray ray, t_list *pln, t_setup *setup)
{
	t_forms		*form;

	form = FORM(pln);
	if (ray.dist >= 0.0)
	{
		form->norm = form->plan.nrml;
		return (diffuse(setup, form, ray, form->plan.mat.col));
	}
	return (setup->background);
}
