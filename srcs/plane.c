/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/27 14:31:38 by psebasti         ###   ########.fr       */
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
	PLAN(form).nrml = ft_vec3normalize_r(PLAN(form).nrml);
	*list = env;
	return (OK);
}

double	hit_plan(t_ray ray, t_forms *form)
{
	double a;
	double b;

	a = ft_vec3dot(ray.dir, form->plan.nrml);
	if (a == 0)
		return (-1);
	b = ft_vec3dot(form->plan.nrml, ft_vec3vop_r(ray.org,
				ft_vec3sop_r(form->plan.nrml, form->plan.dst, '*'), '+'));
	return (-b / a);
}

t_col			intersec_plan(t_ray ray, t_list *pln, t_setup *setup)
{
	t_vec3		norm;

	if (ray.dist >= 0.0)
	{
		norm = PLAN(pln).nrml;
		return (diffuse(norm, pln, ray, PLAN(pln).mat.col));
	}
	return (setup->background);
}
