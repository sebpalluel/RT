/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:56:29 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 22:31:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

size_t			ft_args_to_fd(t_setup *setup)
{
	char		**tmp;

	if (!setup->path || !(tmp = ft_strsplit(setup->path, '/')))
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

int				usage(t_error mode)
{
	static char	*str[ERROR_MAX] = {
		"program exited normally",
		"usage: ./rt [/path/to/map]",
		"error: file doesn't exist or don't have the rights",
		"error: engine is not in the correct format",
		"error: light struct is not in the correct format",
		"error: plane struct is not in the correct format",
		"error: sphere struct is not in the correct format",
		"error: cone struct is not in the correct format",
		"error: cylindre struct is not in the correct format",
		"error: moebius struct is not in the correct format",
		"error: cam struct is not in the correct format",
		"error: scene is not in the correct format",
		"error: objects are not in the correct format",
		"error: dim is not in the correct format [100;4000]",
		"error: texture not allowed for torus and moebius",
		"error: one of the xml struct is not in the correct format",
		"error: one of the material is not in the correct format",
		"error: generative struct is not in the correct format",
		"error: texture struct is not in the correct format"
	};

	ft_putendl(str[mode]);
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
		ft_mlx_process(setup);
	return (ft_quit(setup));
}
