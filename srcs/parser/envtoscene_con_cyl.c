/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoscene_con_cyl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:59:57 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 19:06:46 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rt.h"

void	ft_cone_struct_pop(t_list *form, t_list *env, t_bool *flag,
		size_t *num_arg)
{
	if (ft_strcmp(P_ENV(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&CONE(form).org, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "direction") == 0)
		flag[1] = ft_getvectfromenv(&CONE(form).dir, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "degres") == 0)
		flag[2] = ft_getdoublefromenv(&CONE(form).theta, P_ENV(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 3);
	*num_arg += 1;
}

size_t	ft_cone(t_scene *scn, t_list **list)
{
	t_list		*env;
	t_list		*form;
	t_bool		*flag;
	size_t		num_arg;

	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCONE + NVARMAT_MAX)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCONE + NVARMAT_MAX);
	ft_lstaddend(&scn->forms, ft_newshape());
	form = scn->forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = CON;
	num_arg = 0;
	while (FORM(form)->num_arg < ft_getnumvar(NVARCONE, form)
			&& env && (env = env->next))
		ft_cone_struct_pop(form, env, flag, &num_arg);
	if (ft_checkifallset(flag, ft_getnumvar(NVARCONE, form)) != OK)
		return (scn->error = CONE_ERROR);
	CONE(form).dir = ft_vec3normalize_r(CONE(form).dir);
	*list = env;
	return (OK);
}

void	ft_cylindre_struct_pop(t_list *form, t_list *env, t_bool *flag,
		size_t *num_arg)
{
	if (ft_strcmp(P_ENV(env)->name, "position") == 0)
		flag[0] = ft_getvectfromenv(&CYLI(form).pos, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "direction") == 0)
		flag[1] = ft_getvectfromenv(&CYLI(form).dir, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "radius") == 0)
		flag[2] = ft_getdoublefromenv(&CYLI(form).r, P_ENV(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 3);
	*num_arg += 1;
}

size_t	ft_cylindre(t_scene *scn, t_list **list)
{
	t_list		*env;
	t_list		*form;
	t_bool		*flag;
	size_t		num_arg;

	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCYLINDRE + NVARMAT_MAX)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCYLINDRE + NVARMAT_MAX);
	ft_lstaddend(&scn->forms, ft_newshape());
	form = scn->forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = CYL;
	num_arg = 0;
	while (FORM(form)->num_arg < ft_getnumvar(NVARCYLINDRE, form) && env && (env = env->next))
		ft_cylindre_struct_pop(form, env, flag, &num_arg);
	if (ft_checkifallset(flag, ft_getnumvar(NVARCYLINDRE, form)) != OK)
		return (scn->error = CYLINDRE_ERROR);
	CYLI(form).dir = ft_vec3normalize_r(CYLI(form).dir);
	*list = env;
	return (OK);
}


