/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 17:19:40 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_plane_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENV(env)->name, "normale") == 0)
		flag[0] = ft_getvectfromenv(&PLAN(form).nrml, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "position") == 0)
		flag[1] = ft_getvectfromenv(&PLAN(form).pos, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "color") == 0)
		flag[2] = ft_getcolfromenv(&PLAN(form).mat.col, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "diffuse") == 0)
		flag[3] = ft_getdoublefromenv(&PLAN(form).mat.diffuse, ENV(env)->value);
	if (ft_strcmp(ENV(env)->name, "specular") == 0)
		flag[4] = ft_getdoublefromenv(&PLAN(form).mat.specular, \
				ENV(env)->value);
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
	*list = env;
	return (OK);
}

t_bool			ft_plane_param(t_ray *ray, t_forms *form, double *t)
{
	double		denom;
	t_vec3		dist;

	ft_vec3normalize(&form->plan.nrml);
	ft_vec3normalize(&ray->dir);
	denom = ft_dotproduct(form->plan.nrml, ray->dir);
	if (denom != 0)
	{
		dist = ft_vec3vop_r(form->plan.pos, ray->org, '-');
		*t = ft_dotproduct(pouet, form->plan.nrml) / denom;
		return (*t >= 0);
	}
	return (FALSE);
}
