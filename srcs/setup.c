/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:58:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/16 14:24:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				ft_setup_menu(t_setup *setup)
{
	size_t		xy[2];
	int			ret;

	xy[0] = SETUP.width / 2 - SETUP.width / 14;
	xy[1] = SETUP.height / 2 - SETUP.height / 10;
	mlx_put_image_to_window(SETUP.mlx_ptr, UI_WIN->win_ptr, UI_IMG->image, 0, 0);
	mlx_string_put(SETUP.mlx_ptr, UI_WIN->win_ptr, xy[0], xy[1]\
			, 0x00611DE9, CHOOSE_STR);
	mlx_string_put(SETUP.mlx_ptr, UI_WIN->win_ptr, xy[0], xy[1] + 30\
			, 0x009999FF, SELECT_STR);
	ret = ft_mlx_keytoint(SETUP.key); // permet de selectioner le numero de map
	if (ret >= 0 && SETUP.num_scn < MAX_WINDOW)
	{
		if (ft_select_scene(setup, ret) != OK) // stocke le path vers la map correspondant
			return (SETUP.error = FILE_ERROR); //  dans le cas ou fichier inexistant
		SETUP.scn_num = SETUP.num_scn;
		SETUP.num_scn++;
		SETUP.mode = STATE_OPEN; // rentre dans le mode qui va permettre d'open la map et de parser
	}
	//TODO marquer ici un message au cas ou depase le max window, du type nombre de rendu max atteint
	return (OK);
}

void			ft_start(t_setup *setup)
{
	size_t		xy[2];

	xy[0] = SETUP.width / 2 - SETUP.width / 14;
	xy[1] = SETUP.height / 2 - SETUP.height / 10;
	mlx_string_put(SETUP.mlx_ptr, UI_WIN->win_ptr, xy[0], xy[1], \
			0xFFFFFF, START_STR);
	mlx_string_put(SETUP.mlx_ptr, UI_WIN->win_ptr, xy[0], xy[1] + 30, \
			0xFFFFFF, ENTER_STR);
}

static size_t	ft_alloc_objs(t_setup *setup) // alloue chaque objets
{
	PLANE = (t_plane *)ft_memalloc(sizeof(t_plane) * MAX_OBJ);
	SPHERE = (t_sphere *)ft_memalloc(sizeof(t_sphere) * MAX_OBJ);
	CAM = (t_cam *)ft_memalloc(sizeof(t_cam) * MAX_OBJ);
	LIGHT = (t_light *)ft_memalloc(sizeof(t_light) * MAX_OBJ);
	if (PLANE == NULL || CAM == NULL || LIGHT == NULL || SPHERE == NULL)
		return (ERROR);
	return (OK); // a ce moment tout est alloue, SETUP completement ready
}

static size_t	ft_init_mlx_img(t_setup *setup)
{
	if (!(UI_WIN = (t_mlx*)malloc(sizeof(t_mlx))))
		return (ERROR);
	SETUP.mlx_ptr = mlx_init();
	UI_WIN->win_ptr = mlx_new_window(SETUP.mlx_ptr, SETUP.width, SETUP.height, \
			"rtv1 GUI");
	if (!(UI_IMG = ft_imgnew(SETUP.mlx_ptr, SETUP.width, SETUP.height)))
		return (ERROR);
	return (OK);	
}

static size_t	ft_setup_alloc(t_setup *setup) // tous les define sont juste des racourcis sur la structure setup
{
	SETUP.width = WIDTH;
	SETUP.height = HEIGHT;
	if (SETUP.width < 100 || SETUP.width > 4000 || \
			SETUP.height < 100 || SETUP.height > 4000)
		return (SETUP.error = DIM_ERROR);
	SCN.move_step = MOVE_STEP;
	SCN.rot_step = ROT_STEP;
	SETUP.mutex.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	OBJS = (t_objs *)ft_memalloc(sizeof(t_objs)); // alloue le t_objs qui gere tout les objets 
	OBJS->validobjs = ft_validobjs(); // stocke le type des objets (sous le forme de string) a comparer avec le fichier de config ensuite
	OBJS->builtin = ft_validfuncsptr(); // stocke les pointeurs sur fonction qui correspondent au different type d'objet pour chaque objet (peuple les structures permet verifier erreur de parsing) 
	OBJS->param = ft_objsparam(); // stocke les fonctions parametriques pour chaque formes
	ft_init_mlx_img(setup);
	SETUP.thrd = (pthread_t*)malloc(sizeof(pthread_t) * THREAD);
	SCN.fd = (t_fd *)ft_memalloc(sizeof(t_fd));
	//TODO adapt here for scene
	if (!OBJS->validobjs || !OBJS->builtin || !OBJS->param || !UI_WIN || !UI_IMG \
			|| !SCN.fd || !OBJS || !SETUP.thrd || ft_alloc_objs(setup) != OK) // verifie les mallocs precedent et va initialiser tous les objets
		return (ERROR);
	return (OK);
}

static void		ft_setup_delete(t_setup *setup)
{
	if (setup)
	{
		// TODO do the right functions to free everything
		ft_mlxdelete(UI_WIN, UI_IMG);
		if (OBJS)
		{
			if (PLANE)
				free(PLANE);
			if (SPHERE)
				free(SPHERE);
			if (OBJS->cam)
				free(OBJS->cam);
			if (OBJS->light)
				free(OBJS->light);
			free(OBJS);
		}
		if (SCN.fd)
			ft_fd_delete(SCN.fd);
	}
}

size_t			ft_setup_mode(t_setup *setup, size_t mode)
{
	int			i;

	i = -1;
	if (mode)
		return (ft_setup_alloc(setup));
	else
	{
		usage(setup->error);
		ft_setup_delete(setup);
		free(setup);
		exit(0);
	}
}
