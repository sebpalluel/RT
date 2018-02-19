/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/19 20:12:18 by psebasti         ###   ########.fr       */
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
	*list = env;
	return (OK);
}

//t_bool		ft_plane_param(void *a, t_ray ray, double *dist)
//{
//	t_setup		*setup;
//
//	setup = (t_setup *)a;
//	*dist = 0;
//	ray.size = 0;
//	PL_N++;
//	return (OK);
//}
