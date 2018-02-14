/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/14 18:55:44 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_plane_struct_pop(t_setup *setup, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "position") == 0)
		flag[0] = ft_getvec3fromenv(&PLANE[NPLANE].pos, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "norm") == 0)
		flag[1] = ft_getvec3fromenv(&PLANE[NPLANE].norm, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[4] = ft_getcolfromenv(&PLANE[NPLANE].mat.col, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "diffuse") == 0)
		flag[5] = ft_getdoublefromenv(&PLANE[NPLANE].mat.diffuse, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "specular") == 0)
		flag[6] = ft_getdoublefromenv(&PLANE[NPLANE].mat.specular, \
				ENVSTRUCT(env)->value);
	PLANE[NPLANE].num_arg++;
}


size_t			ft_plane(void *a, t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_bool		*flag;

	setup = (t_setup *)a;
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARPLANE)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARPLANE);
	while (PLANE[NPLANE].num_arg < NVARPLANE && env && (env = env->next))
		ft_plane_struct_pop(setup, env, flag);
	if (ft_checkifallset(flag, NVARPLANE) != OK)
		return (SETUP.error = PLANE_ERROR);
	NPLANE++;
	*list = env;
	return (OK);
}

t_bool		ft_plane_param(void *a, t_ray ray, double *dist)
{
	t_setup		*setup;

	setup = (t_setup *)a;
	*dist = 0;
	ray.size = 0;
	//printf("PL_N %lu\n", PL_N);
	PL_N++;
	return (OK);
}
