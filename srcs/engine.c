/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:41:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/15 15:55:52 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_engine_struct_pop(t_setup *setup, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "width") == 0)
		flag[0] = ft_getsize_tfromenv(&S_WIDTH[1], ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "height") == 0)
		flag[1] = ft_getsize_tfromenv(&S_HEIGHT[1], ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "refr_max") == 0)
		flag[2] = ft_getsize_tfromenv(&SETUP.refr_max, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "refl_max") == 0)
		flag[3] = ft_getsize_tfromenv(&SETUP.refl_max, ENVSTRUCT(env)->value);
	else if (ft_strcmp(ENVSTRUCT(env)->name, "amb_light") == 0)
		flag[4] = ft_getdoublefromenv(&SETUP.amb_light, ENVSTRUCT(env)->value);
	SETUP.num_arg++;
}

static void		ft_create_new_window(t_setup *setup)
{
	MLX[WIN].win_ptr = mlx_new_window(MLX->mlx_ptr, S_WIDTH[WIN], S_HEIGHT[WIN], \
			SETUP.path);
	//IMG[WIN].image = mlx_new_image(MLX->mlx_ptr, S_WIDTH[WIN], S_HEIGHT[WIN]);
	IMG[WIN].image = mlx_xpm_file_to_image(MLX->mlx_ptr, "textures/sky.xpm", \
			(int*)&S_WIDTH[WIN], (int*)&S_HEIGHT[WIN]);
	IMG[WIN].image_addr = mlx_get_data_addr(IMG[WIN].image, \
			&(IMG[WIN].bbp), &(IMG[WIN].size_x), &(IMG[WIN].endian));
	printf("create : image_addr %p. image %p, bbp %d, size_x %d, endian %d\n",\
			IMG[WIN].image_addr, IMG[WIN].image, IMG[WIN].bbp, IMG[WIN].size_x, IMG[WIN].endian);
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
	WIN++;
	if (S_WIDTH[WIN] >= 100 && S_WIDTH[WIN] <= 4000 && \
			S_HEIGHT[WIN] >= 100 && S_HEIGHT[WIN] <= 4000)
		ft_create_new_window(setup);
	else
	{
		WIN--;
		SETUP.error = DIM_ERROR;
	}
	*list = env;
	return (OK);
}
