/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 17:58:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/12 14:54:37 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int				ft_setup_menu(t_setup *setup)
{
	size_t		xy[2];

	xy[0] = SETUP.width / 2 - SETUP.width / 14;
	xy[1] = SETUP.height / 2 - SETUP.height / 10;
	mlx_put_image_to_window(MLX->mlx_ptr, MLX->win_ptr, IMG->image, 0, 0);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, xy[0], xy[1]\
			, 0x00611DE9, CHOOSE_STR);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, xy[0], xy[1] + 30\
			, 0x009999FF, SELECT_STR);
	SETUP.scn_num = ft_mlx_keytoint(SETUP.key); // permet de selectioner le numero de map
	if (SETUP.scn_num < NUM_MAP && SETUP.scn_num >= 0)
	{
		if (ft_select_scene(setup) != OK) // stocke le path vers la map correspondant
			return (SETUP.error = FILE_ERROR); //  dans le cas ou fichier inexistant
		SETUP.mode = STATE_OPEN; // rentre dans le mode qui va permettre d'open la map et de parser
	}
	return (OK);
}

void			ft_start(t_setup *setup)
{
	size_t		xy[2];

	xy[0] = SETUP.width / 2 - SETUP.width / 14;
	xy[1] = SETUP.height / 2 - SETUP.height / 10;
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, xy[0], xy[1], \
			0xFFFFFF, START_STR);
	mlx_string_put(MLX->mlx_ptr, MLX->win_ptr, xy[0], xy[1] + 30, \
			0xFFFFFF, ENTER_STR);
}

static size_t	ft_alloc_objs(t_setup *setup) // alloue chaque objets
{
	PLANE = (t_plane *)ft_memalloc(sizeof(t_plane) * MAX_OBJ);
	SPHERE = (t_sphere *)ft_memalloc(sizeof(t_sphere) * MAX_OBJ);
	OBJS->cam = (t_cam *)ft_memalloc(sizeof(t_cam) * MAX_OBJ);
	OBJS->light = (t_light *)ft_memalloc(sizeof(t_light) * MAX_OBJ);
	if (PLANE == NULL || OBJS->cam == NULL || OBJS->light == NULL \
			|| SPHERE == NULL)
		return (ERROR);
	return (OK); // a ce moment tout est alloue, SETUP completement ready
}

static size_t	ft_setup_alloc(t_setup *setup) // tous les define sont juste des racourcis sur la structure setup
{
	SETUP.width = WIDTH;
	SETUP.height = HEIGHT;
	SETUP.move_step = MOVE_STEP;
	SETUP.rot_step = ROT_STEP;
	OBJS = (t_objs *)ft_memalloc(sizeof(t_objs)); // alloue le t_objs qui gere tout les objets 
	OBJS->validobjs = ft_validobjs(); // stocke le type des objets (sous le forme de string) a comparer avec le fichier de config ensuite
	OBJS->builtin = ft_validfuncsptr(); // stocke les pointeurs sur fonction qui correspondent au different type d'objet pour chaque objet (peuple les structures permet verifier erreur de parsing) 
	OBJS->param = ft_objsparam(); // stocke les fonctions parametriques pour chaque formes
	MLX = ft_initwindow("rtv1", SETUP.width, SETUP.height);
	IMG = ft_imgnew(MLX->mlx_ptr, SETUP.width, SETUP.height);
	FD = (t_fd *)ft_memalloc(sizeof(t_fd));
	if (!OBJS->validobjs || !OBJS->builtin || !OBJS->param || !MLX || !IMG \
			|| !FD || !OBJS || ft_alloc_objs(setup) != OK) // verifie les mallocs precedent et va initialiser tous les objets
		return (ERROR);
	return (OK);
}

static void		ft_setup_delete(t_setup *setup)
{
	if (setup)
	{
		ft_mlxdelete(MLX, IMG);
		if (SETUP.path)
			free(SETUP.path);
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
		if (FD)
			ft_fd_delete(FD);
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
