/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_scene.c                                         :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 17:20:12 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/16 18:12:05 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

size_t			ft_envtosetup(t_setup *setup)
{
	t_list		*env;
	int			i;
	t_bool		flag;

	env = SCN.env;
	//while (env) // can be used to see all the linked list for eventual debug
	//{
	//	if (env && ENVSTRUCT(env))
	//	{
	//		printf("name : %s\n", ENVSTRUCT(env)->name);
	//		printf("value : %s\n", ENVSTRUCT(env)->value);
	//	}
	//	env = env->next;
	//}
	//env = SETUP.env;
	while (env && ENVSTRUCT(env))
	{
		i = -1;
		flag = ERROR; // je part du principe que l'element est inconnu
		while (env && ++i < NUM_OBJS) // NUM_OBJS nombre d'objets que l'on sait gerer
		{
			if (ft_strcmp(ENVSTRUCT(env)->name, SETUP.validobjs[i]) == 0) // ici permet de savoir si cet element est pris en charge
			{

				flag = OK; // dans ce cas la le chainon est valide
				if (SETUP.builtin[i].builtinfunc((void *)setup, &env) != OK) // ici on rentre dans la fonction de l'objet correspondant (par example pour name "sphere" on rentre dans la fonction ft_sphere
					return (ERROR); // dans le cas ou cette structure est mal formatee (information qui manque etc)
				if (env)
					env = env->next; // si c'est ok on passe au chainon suivant qui devra correspondre a un objet qui qui est pris en charge (cam, light, sphere etc.)
			}
		}
		if (flag == ERROR) // ici dans le cas ou aucun objet correspondant
			return (ERROR);
	}
	return (OK);
}

size_t			ft_select_scene(t_setup *setup, int scene)
{
	if (scene == 0)
		SETUP.path = ft_strdup(SCN_PATH_0);
	else if (scene == 1)
		SETUP.path = ft_strdup(SCN_PATH_1);
	if (SETUP.path != NULL)
		return (OK);
	else
		return (ERROR);
}

size_t			ft_alloc_objs(t_setup *setup) // alloue chaque objets
{
	//TODO if new objs adapt
	PLANE = (t_plane *)ft_memalloc(sizeof(t_plane) * MAX_OBJ);
	SPHERE = (t_sphere *)ft_memalloc(sizeof(t_sphere) * MAX_OBJ);
	CAM = (t_cam *)ft_memalloc(sizeof(t_cam) * MAX_OBJ);
	LIGHT = (t_light *)ft_memalloc(sizeof(t_light) * MAX_OBJ);
	if (PLANE == NULL || CAM == NULL || LIGHT == NULL || SPHERE == NULL)
		return (ERROR);
	return (OK); // a ce moment tout est alloue, SETUP completement ready
}

size_t			ft_alloc_new_scene(t_setup *setup)
{
	SCN.fd = (t_fd *)ft_memalloc(sizeof(t_fd));
	ft_args_to_fd(setup);
	SCN.move_step = MOVE_STEP;
	SCN.rot_step = ROT_STEP;
	OBJS = (t_objs *)ft_memalloc(sizeof(t_objs)); // alloue le t_objs qui gere tout les objets 
	if (SCN.fd && OBJS && ft_alloc_objs(setup) == OK)
		return (OK);
	return (ERROR);
}

size_t			ft_open_scene(t_setup *setup)
{
	char		*file;
	char		*line;
	char		*tmp;

	file = NULL;
	line = NULL;
	if (ft_alloc_new_scene(setup) != OK || \
			ft_open(SCN.fd, O_RDONLY, O_APPEND) != OK) // permet de gerer cas d'erreur d'open, pas les droits etc
		return (setup->error = FILE_ERROR);
	while (get_next_line(SCN.fd->fd, &line))
	{
		if (!line) // permet de gerer le cas d'erreur d'ouverture d'un dossier
			return (SETUP.error = FILE_ERROR);
		tmp = file;
		file = ft_strjoin(tmp, line);
		free(tmp);
	}
	// le fichier est bien stocke dans file et il faut le parser
	if (!(SCN.env = ft_parse_scn(setup, file)) || ft_envtosetup(setup) != OK\
			|| SETUP.error != OK) // ft_envlist retourne la list chainee peuplee, ft_envtosetup se charge du parsing et de la population des structures
		return (ERROR);
	if (NCAM == 0)
		return (SETUP.error = CAM_ERROR);
	// appartir de la, on a le setup qui est entierement peuple et aucune erreur
	OBJDEF.objscount = ft_getobjscount(setup); // permet de savoir combien d'objet le raytracer va devoir traiter
	if (!SETUP.num_scn)
		SETUP.num_scn = 1;
	mlx_put_image_to_window(SETUP.mlx_ptr, UI_WIN->win_ptr, UI_IMG->image, 0, 0);
	SETUP.mode = STATE_DRAW; // on peut render !!
	return (OK);
}
