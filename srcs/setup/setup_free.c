/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 13:42:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/02 16:31:04 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_delenvnode(void *content, size_t size)
{
	(void)size;
	if (((t_env*)(content))->name)
		free(((t_env*)(content))->name);
	if (((t_env*)(content))->value)
		free(((t_env*)(content))->value);
	free(content);
}

void		ft_dellistelem(void *content, size_t size)
{
	(void)size;
	if (content)
		free(content);
}

static void	ft_scene_free(t_setup *setup)
{
	if (SCN.img && SCN.img[0] && SCN.img[1] && SCN.win)
	{
		mlx_destroy_image(SCN.win->mlx_ptr, SCN.img[0]->image);
		mlx_destroy_image(SCN.win->mlx_ptr, SCN.img[1]->image);
		mlx_destroy_window(SCN.win->mlx_ptr, SCN.win->win_ptr);
		free(SCN.img[0]);
		free(SCN.img[1]);
		free(SCN.img);
		free(SCN.win);
	}
	ft_lstdel(&SCN.env, ft_delenvnode);
	ft_lstdel(&SCN.forms, ft_dellistelem);
	ft_lstdel(&SCN.lgts, ft_dellistelem);
	ft_lstdel(&SCN.cams, ft_dellistelem);
	if (SCN.fd.path)
		free(SCN.fd.path);
	if (SCN.fd.name)
		free(SCN.fd.name);
}

int			ft_quit(t_setup *setup)
{
	ft_setup_free(setup);
	usage(setup->error);
	exit(0);
}

void		ft_setup_free(t_setup *setup)
{
	setup->scn_num = 0;
	while (setup->scn_num < MAX_WINDOW)
	{
		ft_scene_free(setup);
		setup->scn_num++;
	}
	if (setup->loading)
	{
		mlx_destroy_image(setup->mlx_ptr, setup->loading->image);
		free(setup->loading);
	}
	if (UI_WIN && UI_IMG)
		ft_mlxdelete(UI_WIN, UI_IMG);
	if (setup->scene)
		free(setup->scene);
	if (setup->thrd)
		free(setup->thrd);
	if (setup->path)
		free(setup->path);
}
