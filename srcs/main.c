/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:56:29 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/16 14:24:54 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

size_t			ft_args_to_fd(t_setup *setup)
{
	char		**tmp;

	if (!SCN.path | !(tmp = ft_strsplit(SCN.path, '/')))
		return (ERROR);
	if (tmp[1] != NULL)
	{
		SCN.fd->path = ft_straddchar(tmp[0], '/');
		SCN.fd->name = ft_strdup(tmp[1]);
	}
	else
	{
		SCN.fd->path = ft_strdup("./");
		SCN.fd->name = ft_strdup(tmp[0]);
	}
	if (SCN.fd->path == NULL || SCN.fd->name == NULL)
		return (ERROR);
	ft_tabfree((void **)tmp);
	return (OK);
}

int				usage(int mode)
{
	if (mode == OK)
		ft_putendl("program exited normally");
	else if (mode == ERROR)
		ft_putendl("usage: ./rtv1 map_name");
	else if (mode == FILE_ERROR)
		ft_putendl(FILE_ERROR_S);
	else if (mode == ENG_ERROR)
		ft_putendl(ENG_ERROR_S);
	else if (mode == LIGHT_ERROR)
		ft_putendl(LIGHT_ERROR_S);
	else if (mode == PLANE_ERROR)
		ft_putendl(PLANE_ERROR_S);
	else if (mode == SPHERE_ERROR)
		ft_putendl(SPHERE_ERROR_S);
	else if (mode == CAM_ERROR)
		ft_putendl(CAM_ERROR_S);
	else if (mode == SCN_ERROR)
		ft_putendl(SCN_ERROR_S);
	else if (mode == OBJ_ERROR)
		ft_putendl(OBJ_ERROR_S);
	else if (mode == DIM_ERROR)
		ft_putendl(DIM_ERROR_S);
	return (mode);
}

int				main(int ac, char **av)
{
	t_setup		*setup;

	if (!(setup = (t_setup *)ft_memalloc(sizeof(t_setup))) || \
			!(SETUP.scene = (t_scene *)ft_memalloc(sizeof(t_scene) \
					* MAX_WINDOW)))
		return (-1);
	setup->mode = STATE_START;
	setup->ac = ac;
	ft_color(&setup->background.col, 0, 0, 0);
	SCN.path = av[1] != NULL ? ft_strdup(av[1]) : NULL;
	if ((setup->error = (ac < 3) ? OK : ERROR) == OK \
			&& ft_setup_mode(setup, 1) == OK) // premiere initialisation des structures
		ft_mlx_process(setup); // Si tout est alloue commence avec mode STATE_START
	return (ft_setup_mode(setup, 0));
}
