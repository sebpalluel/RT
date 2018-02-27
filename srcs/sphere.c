/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:40:58 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 17:20:10 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_sphere_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENV(env)->name, "center") == 0)
		flag[0] = ft_getvectfromenv(&SPHERE(form).ctr, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "radius") == 0)
		flag[1] = ft_getdoublefromenv(&SPHERE(form).r, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "color") == 0)
		flag[2] = ft_getcolfromenv(&FORM(form)->mat.col, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "diffuse") == 0)
		flag[3] = ft_getdoublefromenv(&FORM(form)->mat.diffuse, \
				ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "specular") == 0)
		flag[4] = ft_getdoublefromenv(&FORM(form)->mat.specular, \
				ENV(env)->value);
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

t_bool			ft_sphere_param(t_ray *ray, t_forms *form, double *t)
{
	float		t0;
	float		t1;
	t_vec3		l;
	double		abc[3];

	l = ft_vec3vop_r(ray->org, form->sph.ctr, '-');
	abc[0] = ft_dotproduct(ray->dir, ray->dir);
	abc[1] = 2. * ft_dotproduct(ray->dir, l);
	abc[2] = ft_dotproduct(l, l) - SQUARE(form->sph.r);
	if (!solve_quadratic(abc, &t0, &t1))
		return (FALSE);
	if (t0 > t1)
		ft_swap(&t0, &t1, sizeof(float));
	if (t0 < 0)
	{
		t0 = t1;
		if (t0 < 0)
			return (FALSE);
	}
	*t = t0;
	return (TRUE);
}
