/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_torus_moebius.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:20:52 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/21 18:34:48 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_moebius_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&MOEB(form).org, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "axe_x") == 0)
		flag[1] = ft_getvectfromenv(&MOEB(form).axe_x, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "axe_y") == 0)
		flag[2] = ft_getvectfromenv(&MOEB(form).axe_y, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "radius") == 0)
		flag[3] = ft_getdoublefromenv(&MOEB(form).r, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "width") == 0)
		flag[4] = ft_getdoublefromenv(&MOEB(form).width, ENVSTRUCT(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 5);
	FORM(form)->num_arg++;
}

size_t			ft_moebius(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*form;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARMOEBIUS + NVARMAT_MAX)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARMOEBIUS + NVARMAT_MAX);
	ft_lstaddend(&SCN.forms, ft_newshape());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = MOE;
	while (FORM(form)->num_arg < ft_getnumvar(NVARMOEBIUS, form) \
			&& env && (env = env->next))
		ft_moebius_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, ft_getnumvar(NVARMOEBIUS, form)) != OK)
		return (setup->error = MOEBIUS_ERROR);
	MOEB(form).axe_x = ft_vec3normalize_r(MOEB(form).axe_x);
	MOEB(form).axe_y = ft_vec3normalize_r(ft_vec3vop_r(MOEB(form).axe_y, ft_vec3sop_r(MOEB(form).axe_x, ft_vec3dot(MOEB(form).axe_x, MOEB(form).axe_y), '*'), '-'));
	if (MOEB(form).axe_y.x == 0 && MOEB(form).axe_y.y == 0 && MOEB(form).axe_y.z == 0)
		return (setup->error = MOEBIUS_ERROR);
	*list = env;
	return (OK);
}
