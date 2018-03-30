/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoscene_tor_moe.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:06:35 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 19:10:33 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rt.h"

void			ft_moebius_struct_pop(t_list *form, t_list *env, t_bool *flag,
		size_t *num_arg)
{
	if (ft_strcmp(P_ENV(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&MOEB(form).org, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "axe_x") == 0)
		flag[1] = ft_getvectfromenv(&MOEB(form).axe_x, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "axe_y") == 0)
		flag[2] = ft_getvectfromenv(&MOEB(form).axe_y, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "radius") == 0)
		flag[3] = ft_getdoublefromenv(&MOEB(form).r, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "width") == 0)
		flag[4] = ft_getdoublefromenv(&MOEB(form).width, P_ENV(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 5);
	*num_arg += 1;
}

size_t			ft_moebius(t_scene *scn, t_list **list)
{
	t_list		*env;
	t_list		*form;
	t_bool		*flag;
	size_t		num_arg;

	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARMOEBIUS + NVARMAT_MAX)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARMOEBIUS + NVARMAT_MAX);
	ft_lstaddend(&scn->forms, ft_newshape());
	form = scn->forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = MOE;
	num_arg = 0;
	while (FORM(form)->num_arg < ft_getnumvar(NVARMOEBIUS, form) \
			&& env && (env = env->next))
		ft_moebius_struct_pop(form, env, flag, &num_arg);
	if (ft_checkifallset(flag, ft_getnumvar(NVARMOEBIUS, form)) != OK)
		return (scn->error = MOEBIUS_ERROR);
	MOEB(form).axe_x = ft_vec3normalize_r(MOEB(form).axe_x);
	MOEB(form).axe_y = ft_vec3normalize_r(MOEB(form).axe_y);
	*list = env;
	return (OK);
}

void			ft_torus_struct_pop(t_list *form, t_list *env, t_bool *flag,
		size_t *num_arg)
{
	if (ft_strcmp(P_ENV(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&TORU(form).org, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "direction") == 0)
		flag[1] = ft_getvectfromenv(&TORU(form).dir, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "small_radius") == 0)
		flag[2] = ft_getdoublefromenv(&TORU(form).s_r, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "big_radius") == 0)
		flag[3] = ft_getdoublefromenv(&TORU(form).b_r, P_ENV(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 4);
	*num_arg += 1;
}

size_t			ft_torus(t_scene *scn, t_list **list)
{
	t_list		*env;
	t_list		*form;
	t_bool		*flag;
	size_t		num_arg;

	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARTORUS + NVARMAT_MAX)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARTORUS + NVARMAT_MAX);
	ft_lstaddend(&scn->forms, ft_newshape());
	form = scn->forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = TOR;
	num_arg = 0;
	while (FORM(form)->num_arg < ft_getnumvar(NVARTORUS, form) \
			&& env && (env = env->next))
		ft_torus_struct_pop(form, env, flag, &num_arg);
	if (ft_checkifallset(flag, ft_getnumvar(NVARTORUS, form)) != OK)
		return (scn->error = TORUS_ERROR);
	TORU(form).dir = ft_vec3normalize_r(TORU(form).dir);
	*list = env;
	return (OK);
}
