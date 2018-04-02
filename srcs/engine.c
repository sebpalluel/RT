/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:41:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/02 16:26:05 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_engine_struct_pop(t_setup *setup, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "width") == 0)
		flag[0] = ft_getsize_tfromenv(&SCN.width, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "height") == 0)
		flag[1] = ft_getsize_tfromenv(&SCN.height, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "refr_max") == 0)
		flag[2] = ft_getsize_tfromenv(&SCN.refr_max, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "refl_max") == 0)
		flag[3] = ft_getsize_tfromenv(&SCN.refl_max, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "amb_light") == 0)
		flag[4] = ft_getdoublefromenv(&SCN.amb_light, ENVSTRUCT(env)->value);
	SCN.num_arg++;
}

static void		ft_create_new_window(t_setup *setup)
{
	SCN.win = (t_mlx *)ft_memalloc(sizeof(t_mlx));
	SCN.win->win_ptr = mlx_new_window(setup->mlx_ptr, SCN.width, \
			SCN.height, setup->path);
	SCN.img = (t_img**)ft_memalloc(sizeof(t_img*) * 2);
	if (!SCN.win || !SCN.win->win_ptr || !SCN.img || \
			!(SCN.img[0] = ft_imgnew(setup->mlx_ptr, SCN.width, SCN.height)) ||\
			!(SCN.img[1] = ft_imgnew(setup->mlx_ptr, SCN.width, SCN.height)))
		setup->error = ERROR;
	else
	{
		SCN.win->mlx_ptr = setup->mlx_ptr;
		mlx_hook(SCN.win->win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, \
				ft_quit, setup);
		mlx_put_image_to_window(setup->mlx_ptr, SCN.win->win_ptr, \
				setup->loading->image, SCN.width / 3., SCN.height / 2.7);
	}
}

size_t			ft_engine(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARENG)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARENG);
	while (SCN.num_arg < NVARENG && env && (env = env->next))
		ft_engine_struct_pop(setup, env, flag);
	if (ft_checkifallset(flag, NVARENG) != OK)
		return (setup->error = ENG_ERROR);
	if (SCN.width >= 100 && SCN.width <= 4000 && \
			SCN.height >= 100 && SCN.height <= 4000)
		ft_create_new_window(setup);
	else
		setup->error = DIM_ERROR;
	*list = env;
	return (OK);
}
