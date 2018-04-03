/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoscene_con_cyl.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:44:08 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 21:38:09 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_cone_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&CONE(form).org, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "direction") == 0)
		flag[1] = ft_getvectfromenv(&CONE(form).dir, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "degres") == 0)
		flag[2] = ft_getdoublefromenv(&CONE(form).theta, ENVSTRUCT(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 3);
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
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCONE + NVARMAT_MAX)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCONE + NVARMAT_MAX);
	ft_lstaddend(&SCN.forms, ft_newshape());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = CON;
	while (FORM(form)->num_arg < ft_getnumvar(NVARCONE, form) \
			&& env && (env = env->next))
		ft_cone_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, ft_getnumvar(NVARCONE, form)) != OK)
		return (setup->error = CONE_ERROR);
	CONE(form).dir = ft_vec3normalize_r(CONE(form).dir);
	*list = env;
	return (OK);
}

void			ft_cylindre_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "position") == 0)
		flag[0] = ft_getvectfromenv(&CYLI(form).pos, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "direction") == 0)
		flag[1] = ft_getvectfromenv(&CYLI(form).dir, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "radius") == 0)
		flag[2] = ft_getdoublefromenv(&CYLI(form).r, ENVSTRUCT(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 3);
	FORM(form)->num_arg++;
}

size_t			ft_cylindre(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*form;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCYLINDRE + NVARMAT_MAX)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCYLINDRE + NVARMAT_MAX);
	ft_lstaddend(&SCN.forms, ft_newshape());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = CYL;
	while (FORM(form)->num_arg < ft_getnumvar(NVARCYLINDRE, form) && env && \
			(env = env->next))
		ft_cylindre_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, ft_getnumvar(NVARCYLINDRE, form)) != OK)
		return (setup->error = CYLINDRE_ERROR);
	CYLI(form).dir = ft_vec3normalize_r(CYLI(form).dir);
	*list = env;
	return (OK);
}
