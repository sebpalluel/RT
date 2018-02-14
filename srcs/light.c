/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/14 11:04:44 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_light_struct_pop(t_setup *setup, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "light_pos") == 0)
		flag[0] = ft_getvec3fromenv(&LIGHT[NLIGHT].pos, ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "light_intensity") == 0)
		flag[1] = ft_getfloatfromenv(&LIGHT[NLIGHT].intensity, \
				ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "light_col") == 0)
		flag[2] = ft_getcolfromenv(&LIGHT[NLIGHT].mat.col, ENVSTRUCT(env)->value);
	LIGHT[NLIGHT].num_arg++;
}

size_t			ft_light(void *a, t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_bool		*flag;

	setup = (t_setup *)a;
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARLIGHT)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARLIGHT);
	while (LIGHT[NLIGHT].num_arg < NVARLIGHT && env && (env = env->next))
		ft_light_struct_pop(setup, env, flag);
	if (ft_checkifallset(flag, NVARLIGHT) != OK)
		return (SETUP.error = LIGHT_ERROR);
	NLIGHT++;
	*list = env;
	return (OK);
}
