/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:36 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/10 18:30:26 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void		ft_cam_struct_pop(t_setup *setup, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "cam_pos") == 0)
		flag[0] = ft_getvec3fromenv(&CAM[NCAM].pos, ENVSTRUCT(env)->value); // cette fonction attend une string qui decrit un vecteur qui va peupler cam_pos, return ERROR si pas bon format
	else if (ft_strcmp(ENVSTRUCT(env)->name, "cam_dir") == 0)
		flag[1] = ft_getvec3fromenv(&CAM[NCAM].dir, ENVSTRUCT(env)->value);
	CAM[NCAM].num_arg++;
}

size_t			ft_cam(void *a, t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_bool		*flag;

	setup = (t_setup *)a;
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCAM))) // initialise un tableau de bool a ERROR, pour verifier que tout est bien formate a la fin
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCAM);
	while (CAM[NCAM].num_arg < NVARCAM && env && (env = env->next)) // je passe au node suivant, qui est sense etre cam_pos ou cam_dir
		ft_cam_struct_pop(setup, env, flag); // va trouver la variable correspondante au node (ici cam_pos ou cam_dir) et peuple cette variable + cherche si erreur
	if (ft_checkifallset(flag, NVARCAM) != OK) // ici si tout le tableau de flag est a OK, c'est que pas d'erreur
		return (SETUP.error = CAM_ERROR);
	NCAM++; // passe a la camera suivant si il y en a, permet en meme temps d'indiquer le nombre total de camera
	*list = env;
	return (OK);
}

// See: http://people.cs.clemson.edu/~dhouse/courses/405/notes/raycamera.pdf
void			ft_setup_cam(t_setup *setup)
{
	int			cam_n;
	t_vec3		u_x;
	t_vec3		u_y;
	t_vec3		c_0;

	cam_n = -1;
	while (++cam_n < (int)NCAM)
	{
		CAM[cam_n].focal_len = 360.; // gere l'ouverture du champ de vision
		//ft_vec3vop_r (gere toutes les operations de vecteur sur vecteur et return le vecteur resultant)
		//ft_vec3sop_r (gere toutes les operations de vecteur sur double et return le vecteur resultant)
		c_0 = ft_vec3vop_r(CAM[cam_n].pos, ft_vec3sop_r(CAM[cam_n].dir, \
					CAM[cam_n].focal_len, '*'), '+');
		//printf("c_0 : %f, %f, %f\n", c_0.x, c_0.y, c_0.z);
		u_x = ft_vec3unit(ft_vec3vop_r(CAM[cam_n].dir, \
					ft_vec3_r(0., -1., 0.), 'c'));
		u_y = ft_vec3vop_r(ft_vec3sop_r(CAM[cam_n].dir, -1.0, '*'), u_x, 'c');
		CAM[cam_n].plane_center = c_0;
		CAM[cam_n].plane_dirX = u_x;
		CAM[cam_n].plane_dirY = u_y;
		//	printf("CAM[cam_n] dirX : %f, %f, %f\nCAM[cam_n] dirY : %f, %f, %f\nCAM[cam_n] center : %f, %f, %f\n", \
		//				CAM[cam_n].plane_dirX.x, CAM[cam_n].plane_dirX.y, CAM[cam_n].plane_dirX.z, \
		//				CAM[cam_n].plane_dirY.x, CAM[cam_n].plane_dirY.y, CAM[cam_n].plane_dirY.z, \
		//				CAM[cam_n].plane_center.x, CAM[cam_n].plane_center.y, CAM[cam_n].plane_center.z);
	}
}


