/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/28 16:00:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_plane_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "normale") == 0)
		flag[0] = ft_getvectfromenv(&PLAN(form).nrml, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "distance") == 0)
		flag[1] = ft_getdoublefromenv(&PLAN(form).dst, ENVSTRUCT(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 2);
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
	ft_lstaddend(&SCN.forms, ft_newshape());
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

t_vec3			normal_plane(t_ray ray, t_list *plane)
{
	t_vec3	norm;

	norm = PLAN(plane).nrml;
	if (ft_vec3dot(PLAN(plane).nrml, ray.dir) > 0)
		norm = ft_vec3sop_r(PLAN(plane).nrml, -1, '*');
	return (norm);
}

double	hit_plan(t_ray ray, t_shape *form)
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
		norm = normal_plane(ray, pln);
		return (diffuse(norm, pln, ray, FORM(pln)->mat));
	}
	return (setup->background);
}
