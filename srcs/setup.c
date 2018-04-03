/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:58:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/02 16:43:46 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				ft_setup_menu(t_setup *setup)
{
	size_t		xy[2];
	int			ret;

	xy[0] = setup->width / 2 - setup->width / 14;
	xy[1] = setup->height / 2 - setup->height / 10;
	mlx_put_image_to_window(setup->mlx_ptr, UI_WIN->win_ptr,
		UI_IMG->image, 0, 0);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, xy[0], xy[1]\
			, 0x00611DE9, CHOOSE_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, xy[0], xy[1] + 30\
			, 0x009999FF, SELECT_STR);
	ret = ft_mlx_keytoint(setup->key);
	if (ret >= 0 && setup->num_scn < MAX_WINDOW)
	{
		if (ft_select_scene(setup, ret) != OK)
			return (setup->error = FILE_ERROR);
		setup->scn_num = setup->num_scn;
		setup->num_scn++;
		setup->mode = STATE_OPEN;
	}
	return (OK);
}

void			ft_start(t_setup *setup)
{
	size_t		xy[2];

	xy[0] = setup->width / 2 - setup->width / 14;
	xy[1] = setup->height / 2 - setup->height / 10;
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, xy[0], xy[1], \
			0xFFFFFF, START_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, xy[0], xy[1] + 30, \
			0xFFFFFF, ENTER_STR);
}

static size_t	ft_init_mlx_img(t_setup *setup)
{
	if (!(UI_WIN = (t_mlx*)malloc(sizeof(t_mlx))))
		return (setup->error = ERROR);
	setup->mlx_ptr = mlx_init();
	UI_WIN->mlx_ptr = setup->mlx_ptr;
	UI_WIN->win_ptr = mlx_new_window(setup->mlx_ptr, setup->width, \
			setup->height, "RT GUI");
	UI_IMG = ft_imgnew(setup->mlx_ptr, setup->width, setup->height);
	setup->loading = ft_xmpnew(setup->mlx_ptr, "textures/loading.xpm", \
			100, 100);
	if (!UI_IMG || !setup->loading)
		return (setup->error = ERROR);
	return (OK);
}

t_setup			*ft_setup_alloc(t_setup *setup)
{
	setup->width = WIDTH;
	setup->height = HEIGHT;
	if (setup->width < 100 || setup->width > 4000 || \
			setup->height < 100 || setup->height > 4000)
	{
		setup->error = DIM_ERROR;
		return (NULL);
	}
	setup->thrd = (pthread_t*)malloc(sizeof(pthread_t) * THREAD);
	setup->mutex.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	ft_init_mlx_img(setup);
	setup->textures = get_texture();
	setup->scene = (t_scene *)ft_memalloc(sizeof(t_scene) * MAX_WINDOW);
	if (setup->error != OK || !setup->thrd || !setup->scene)
		return (NULL);
	return (setup);
}
