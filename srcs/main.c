/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 15:56:29 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/29 17:25:36 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*size_t			ft_args_to_fd(t_setup *setup)*/
/*{*/
	/*char		**tmp;*/

	/*if (!setup->path | !(tmp = ft_strsplit(setup->path, '/')))*/
		/*return (ERROR);*/
	/*if (tmp[0] && tmp[1])*/
	/*{*/
		/*SCN.fd.path = ft_straddchar(tmp[0], '/');*/
		/*SCN.fd.name = ft_strdup(tmp[1]);*/
	/*}*/
	/*else if (tmp[0])*/
	/*{*/
		/*SCN.fd.path = ft_strdup("./");*/
		/*SCN.fd.name = ft_strdup(tmp[0]);*/
	/*}*/
	/*if (SCN.fd.path == NULL || SCN.fd.name == NULL)*/
		/*return (ERROR);*/
	/*ft_tabfree((void **)tmp);*/
	/*return (OK);*/
/*}*/

int				main(int ac, char **av)
{
	SDL_Event	e;
	uint32_t	quit;

	// PRE LAUNCH EVENTS
	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				quit = 1;
		}
	}
	return (0);
}

/*int				main(int ac, char **av)*/
/*{*/
	/*t_setup		*setup;*/

	/*if (!(setup = ft_setup_alloc(get_st())))*/
		/*return (EXIT_FAILURE);*/
	/*setup->mode = STATE_START;*/
	/*setup->ac = ac;*/
	/*setup->background = ft_col_r(0, 0, 0, 0);*/
	/*setup->path = av[1] != NULL ? ft_strdup(av[1]) : NULL;*/
	/*if ((setup->error = (ac < 3) ? OK : ERROR) == OK)*/
		/*ft_mlx_process(setup); // Si tout est alloue commence avec mode STATE_START*/
	/*return (ft_quit(setup));*/
/*}*/
