/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 17:41:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/14 20:11:08 by psebasti         ###   ########.fr       */
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

static	void	ft_delete_create_window(t_setup *setup)
{
	mlx_destroy_window(MLX->mlx_ptr, MLX->win_ptr);
	mlx_destroy_image(MLX->mlx_ptr, IMG->image);
	MLX->win_ptr = mlx_new_window(MLX->mlx_ptr, SETUP.width, SETUP.height, \
			SETUP.path);
	IMG->image = mlx_new_image(MLX->mlx_ptr, SETUP.width, SETUP.height);
	IMG->image_addr = mlx_get_data_addr(IMG->image, \
								&(IMG->bbp), &(IMG->size_x), &(IMG->endian));
}

size_t			ft_engine(void *a, t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_bool		*flag;
	size_t		w_h_value[2];

	setup = (t_setup *)a;
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARENG)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARENG);
	w_h_value[0] = SETUP.width;
	w_h_value[1] = SETUP.height;
	while (SETUP.num_arg < NVARENG && env && (env = env->next))
		ft_engine_struct_pop(setup, env, flag);
	if (ft_checkifallset(flag, NVARENG) != OK)
		return (SETUP.error = ENG_ERROR);
	if (SETUP.width != w_h_value[0] || SETUP.height != w_h_value[1])
		ft_delete_create_window(setup);
	*list = env;
	return (OK);
}
