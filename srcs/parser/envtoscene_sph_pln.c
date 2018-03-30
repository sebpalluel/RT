/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoscene_sph_pln.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:11:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 18:59:10 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rt.h"

void			ft_plane_struct_pop(t_list *form, t_list *env, t_bool *flag,
		size_t *num_arg)
{
	if (ft_strcmp(P_ENV(env)->name, "normale") == 0)
		flag[0] = ft_getvectfromenv(&PLAN(form).nrml, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "distance") == 0)
		flag[1] = ft_getdoublefromenv(&PLAN(form).dst, P_ENV(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 2);
	*num_arg += 1;
}

size_t			ft_plane(t_scene *scn, t_list **list)
{
	t_list		*env;
	t_list		*form;
	t_bool		*flag;
	size_t		num_arg;

	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARPLANE + NVARMAT_MAX)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARPLANE + NVARMAT_MAX);
	ft_lstaddend(&scn->forms, ft_newshape());
	form = scn->forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = PLN;
	num_arg = 0;
	while (num_arg < ft_getnumvar(NVARPLANE, form) \
			&& env && (env = env->next))
		ft_plane_struct_pop(form, env, flag, &num_arg);
	if (ft_checkifallset(flag, ft_getnumvar(NVARPLANE, form)) != OK)
		return (PLANE_ERROR);
	PLAN(form).nrml = ft_vec3normalize_r(PLAN(form).nrml);
	*list = env;
	return (OK);
}

void			ft_sphere_struct_pop(t_list *form, t_list *env, t_bool *flag,
		size_t *num_arg)
{
	if (ft_strcmp(P_ENV(env)->name, "center") == 0)
		flag[0] = ft_getvectfromenv(&SPHERE(form).ctr, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "radius") == 0)
		flag[1] = ft_getdoublefromenv(&SPHERE(form).r, P_ENV(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 2);
	*num_arg += 1;
}

size_t			ft_sphere(t_scene *scn, t_list **list)
{
	t_list		*env;
	t_list		*form;
	t_bool		*flag;
	size_t		num_arg;

	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARSPHERE + NVARMAT_MAX)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARSPHERE + NVARMAT_MAX);
	ft_lstaddend(&scn->forms, ft_newshape());
	form = scn->forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = SPH;
	num_arg = 0;
	while (FORM(form)->num_arg < ft_getnumvar(NVARSPHERE, form) 
			&& env && (env = env->next))
		ft_sphere_struct_pop(form, env, flag, &num_arg);
	if (ft_checkifallset(flag, ft_getnumvar(NVARSPHERE, form)) != OK)
		return (scn->error = SPHERE_ERROR);
	*list = env;
	return (OK);
}


