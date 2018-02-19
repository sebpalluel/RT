/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:58:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/19 17:19:48 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				ft_setup_menu(t_setup *setup)
{
	size_t		xy[2];
	int			ret;

	xy[0] = setup->width / 2 - setup->width / 14;
	xy[1] = setup->height / 2 - setup->height / 10;
	mlx_put_image_to_window(setup->mlx_ptr, UI_WIN->win_ptr, UI_IMG->image, 0, 0);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, xy[0], xy[1]\
			, 0x00611DE9, CHOOSE_STR);
	mlx_string_put(setup->mlx_ptr, UI_WIN->win_ptr, xy[0], xy[1] + 30\
			, 0x009999FF, SELECT_STR);
	ret = ft_mlx_keytoint(setup->key); // permet de selectioner le numero de map
	if (ret >= 0 && setup->num_scn < MAX_WINDOW)
	{
		if (ft_select_scene(setup, ret) != OK) // stocke le path vers la map correspondant
			return (setup->error = FILE_ERROR); //  dans le cas ou fichier inexistant
		setup->scn_num = setup->num_scn;
		setup->num_scn++;
		setup->mode = STATE_OPEN; // rentre dans le mode qui va permettre d'open la map et de parser
	}
	//TODO marquer ici un message au cas ou depase le max window, du type nombre de rendu max atteint
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
		return (ERROR);
	setup->mlx_ptr = mlx_init();
	UI_WIN->win_ptr = mlx_new_window(setup->mlx_ptr, setup->width, setup->height, \
			"rtv1 GUI");
	if (!(UI_IMG = ft_imgnew(setup->mlx_ptr, setup->width, setup->height)))
		return (ERROR);
	return (OK);	
}

t_setup			*ft_setup_alloc(t_setup *setup) // tous les define sont juste des racourcis sur la structure setup
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
	setup->validobjs = ft_validobjs(); // stocke le type des objets (sous le forme de string) a comparer avec le fichier de config ensuite
	setup->builtin = ft_validfuncsptr(); // stocke les pointeurs sur fonction qui correspondent au different type d'objet pour chaque objet (peuple les structures permet verifier erreur de parsing) 
	setup->param = ft_objsparam(); // stocke les fonctions parametriques pour chaque formes
	ft_init_mlx_img(setup);
	setup->scene = (t_scene *)ft_memalloc(sizeof(t_scene) * MAX_WINDOW);
	if (!setup->validobjs || !setup->builtin || !setup->param || !UI_WIN || \
			!UI_IMG || !setup->thrd || !setup->scene) // verifie les mallocs precedent et va initialiser tous les objets
		return (NULL);
	return (setup);
}

static void		ft_setup_delete(t_setup *setup)
{
	if (setup)
	{
	//	// TODO do the right functions to free everything
	//	//ft_mlxdelete(UI_WIN, UI_IMG);
	//	if (OBJS)
	//	{
	//		if (PLANE)
	//			free(PLANE);
	//		if (SPHERE)
	//			free(SPHERE);
	//		if (OBJS->cam)
	//			free(OBJS->cam);
	//		if (OBJS->light)
	//			free(OBJS->light);
	//		free(OBJS);
	//	}
	//	if (SCN.fd)
	//		ft_fd_delete(SCN.fd);
	}
}

int				ft_quit(t_setup *setup)
{
		usage(setup->error);
		ft_setup_delete(setup);
		free(setup);
		exit(0);
}
