/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/14 14:10:25 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_light_struct_pop(t_setup *setup, t_list *env, t_bool *flag)
{	
	if (ft_strcmp(ENVSTRUCT(env)->name, "type") == 0)
		flag[0] = ft_getsize_tfromenv(&LIGHT[NLIGHT].type, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "position") == 0)
		flag[1] = ft_getvec3fromenv(&LIGHT[NLIGHT].pos, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[2] = ft_getcolfromenv(&LIGHT[NLIGHT].col, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "intensity") == 0)
		flag[3] = ft_getdoublefromenv(&LIGHT[NLIGHT].intensity, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "radius") == 0)
		flag[4] = ft_getdoublefromenv(&LIGHT[NLIGHT].radius, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "fallof") == 0)
		flag[5] = ft_getdoublefromenv(&LIGHT[NLIGHT].fallof, \
				ENVSTRUCT(env)->value);
	if (LIGHT[NLIGHT].type && ft_strcmp(ENVSTRUCT(env)->name, "focal_len") == 0)
		flag[6] = ft_getdoublefromenv(&LIGHT[NLIGHT].focal_len, \
				ENVSTRUCT(env)->value);
	if (LIGHT[NLIGHT].type && ft_strcmp(ENVSTRUCT(env)->name, "direction") == 0)
		flag[7] = ft_getvec3fromenv(&LIGHT[NLIGHT].dir, ENVSTRUCT(env)->value);
	LIGHT[NLIGHT].num_arg++;
}

size_t			ft_light(void *a, t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_bool		*flag;
	size_t		num_arg;

	setup = (t_setup *)a;
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARLIGHT)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARLIGHT);
	while (LIGHT[NLIGHT].num_arg < (num_arg = (LIGHT[NLIGHT].type ? \
				NVARLIGHT : NVARLIGHT - 2)) && env && (env = env->next))
	{
		ft_light_struct_pop(setup, env, flag);
		printf("name light : %s\n", ENVSTRUCT(env)->name);
	}
	if (ft_checkifallset(flag, num_arg) != OK)
		return (SETUP.error = LIGHT_ERROR);
	NLIGHT++;
	*list = env;
	return (OK);
}
