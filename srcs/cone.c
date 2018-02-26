/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 20:19:17 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 17:17:17 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_cone_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENV(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&CONE(form).org, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "direction") == 0)
		flag[1] = ft_getvectfromenv(&CONE(form).dir, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "degres") == 0)
		flag[2] = ft_getdoublefromenv(&CONE(form).theta, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "color") == 0)
		flag[3] = ft_getcolfromenv(&CONE(form).mat.col, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "diffuse") == 0)
		flag[4] = ft_getdoublefromenv(&CONE(form).mat.diffuse, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "specular") == 0)
		flag[5] = ft_getdoublefromenv(&CONE(form).mat.specular, \
				ENV(env)->value);
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
	// Normaliser ici pour l instant l67
	if (ft_checkifallset(flag, NVARCONE) != OK)
		return (setup->error = CONE_ERROR);
	*list = env;
	return (OK);
}

t_bool			ft_cone_intersect(t_ray *ray, t_forms *form, double *t)
{
	float		k;
	double		dv;
	double		distv;
	double		abc[3];
	t_vec3		dist;

	ft_normalize(&form->cone.dir);
	k = tan(DEG2RAD(form->cone.theta) / 2);
	dist = ft_vec3vop_r(ray->org, form->cone.org, '-');
	dv = ft_dotproduct(ray->dir, form->cone.dir);
	distv = ft_dotproduct(dist, form->cone.dir);
	abc[0] = ft_dotproduct(ray->dir, ray->dir) - (1 + k * k) * (dv * dv);
	abc[1] = 2 * (ft_dotproduct(ray->dir, dist) - (1 + k * k) * dv * distv);
	abc[2] = ft_dotproduct(dist, dist) - (1 + k * k) * (distv * distv);
	return (ft_solve_quadra(abc, t));
}
