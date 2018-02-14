/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:41:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/14 11:41:21 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_engine_struct_pop(t_setup *setup, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "width") == 0)
		flag[0] = ft_getsize_tfromenv(&SETUP.width, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "height") == 0)
		flag[1] = ft_getsize_tfromenv(&SETUP.height, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "refr_max") == 0)
		flag[2] = ft_getsize_tfromenv(&SETUP.refr_max, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "refl_max") == 0)
		flag[3] = ft_getsize_tfromenv(&SETUP.refl_max, ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "amb_light") == 0)
		flag[4] = ft_getdoublefromenv(&SETUP.amb_light, ENVSTRUCT(env)->value);
	SETUP.num_arg++;
}

size_t			ft_engine(void *a, t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_bool		*flag;

	setup = (t_setup *)a;
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARENG)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARENG);
	while (SETUP.num_arg < NVARENG && env && (env = env->next))
		ft_engine_struct_pop(setup, env, flag);
	if (ft_checkifallset(flag, NVARENG) != OK)
		return (SETUP.error = ENG_ERROR);
	*list = env;
	return (OK);
}
