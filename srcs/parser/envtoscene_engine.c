/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envtoscene_engine.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 17:39:04 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 18:02:14 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rt.h"

void			ft_engine_struct_pop(t_scene *scn, t_list *env, t_bool *flag,
		size_t *num_arg)
{
	if (ft_strcmp(P_ENV(env)->name, "refr_max") == 0)
		flag[0] = ft_getsize_tfromenv(&scn->refr_max, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "refl_max") == 0)
		flag[1] = ft_getsize_tfromenv(&scn->refl_max, P_ENV(env)->value);
	if (ft_strcmp(P_ENV(env)->name, "amb_light") == 0)
		flag[2] = ft_getdoublefromenv(&scn->amb_light, P_ENV(env)->value);
	*num_arg += 1;
}

//static void		ft_create_new_window(t_setup *setup)
//{
//	SCN.win = (t_mlx *)ft_memalloc(sizeof(t_mlx));
//	SCN.win->win_ptr = mlx_new_window(setup->mlx_ptr, SCN.width, \
//			SCN.height, setup->path);
//	SCN.img = (t_img**)ft_memalloc(sizeof(t_img*) * 2);
//	if (!SCN.win || !SCN.win->win_ptr || !SCN.img || \
//			!(SCN.img[0] = ft_imgnew(setup->mlx_ptr, SCN.width, SCN.height)) ||\
//			!(SCN.img[1] = ft_imgnew(setup->mlx_ptr, SCN.width, SCN.height)))
//		setup->error = ERROR;
//	else
//		SCN.win->mlx_ptr = setup->mlx_ptr;
//	mlx_hook(SCN.win->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, \
//			ft_quit, setup);
//}

size_t			ft_engine(t_scene *scn, t_list **list)
{
	t_list		*env;
	t_bool		*flag;
	size_t		num_arg;

	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARENG)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARENG);
	num_arg = 0;
	while (num_arg < NVARENG && env && (env = env->next))
		ft_engine_struct_pop(scn, env, flag, &num_arg);
	if (ft_checkifallset(flag, NVARENG) != OK)
		return (scn->error = ENG_ERROR);
		//ft_create_new_window(setup);
	*list = env;
	return (OK);
}
