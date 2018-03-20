/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:56:29 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/20 14:10:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
size_t			ft_args_to_fd(t_setup *setup)
{
	char		**tmp;

	if (!setup->path | !(tmp = ft_strsplit(setup->path, '/')))
		return (ERROR);
	if (tmp[0] && tmp[1])
	{
		SCN.fd.path = ft_straddchar(tmp[0], '/');
		SCN.fd.name = ft_strdup(tmp[1]);
	}
	else if (tmp[0])
	{
		SCN.fd.path = ft_strdup("./");
		SCN.fd.name = ft_strdup(tmp[0]);
	}
	if (SCN.fd.path == NULL || SCN.fd.name == NULL)
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
	else if (mode == CONE_ERROR)
		ft_putendl(CONE_ERROR_S);
	else if (mode == CYLINDRE_ERROR)
		ft_putendl(CYL_ERROR_S);
	else if (mode == TORUS_ERROR)
		ft_putendl(TOR_ERROR_S);
	else if (mode == MOEBIUS_ERROR)
		ft_putendl(MOE_ERROR_S);
	else if (mode == CAM_ERROR)
		ft_putendl(CAM_ERROR_S);
	else if (mode == SCN_ERROR)
		ft_putendl(SCN_ERROR_S);
	else if (mode == OBJ_ERROR)
		ft_putendl(OBJ_ERROR_S);
	else if (mode == DIM_ERROR)
		ft_putendl(DIM_ERROR_S);
	else if (mode == XML_ERROR)
		ft_putendl(XML_ERROR_S);
	else if (mode == MAT_ERROR)
		ft_putendl(MAT_ERROR_S);
	else if (mode == GEN_ERROR)
		ft_putendl(GEN_ERROR_S);
	else if (mode == TEX_ERROR)
		ft_putendl(TEX_ERROR_S);
	return (mode);
}

int				main(int ac, char **av)
{
	t_setup		*setup;

	if (!(setup = ft_setup_alloc(get_st())))
		return (EXIT_FAILURE);
	setup->mode = STATE_START;
	setup->ac = ac;
	setup->background = ft_col_r(0, 0, 0, 0);
	setup->path = av[1] != NULL ? ft_strdup(av[1]) : NULL;
	if ((setup->error = (ac < 3) ? OK : ERROR) == OK)
		ft_mlx_process(setup); // Si tout est alloue commence avec mode STATE_START
	return (ft_quit(setup));
}
