/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:36 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/22 15:44:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"


void			ft_look_at(t_setup *setup, t_cam *cam)
{
	t_vec3		forward;
	t_vec3		right;
	t_vec3		up;

	forward = ft_vec3normalize_r(ft_vec3vop_r(cam->org, cam->look_at, '-'));
	right = ft_vec3vop_r(ft_vec3normalize_r(ft_vec3_r(0, 1, 0)), forward, 'c');
	up = ft_vec3vop_r(forward, right, 'c');
	setup->camToWorld[0][0] = right.x; 
	setup->camToWorld[0][1] = right.y;
	setup->camToWorld[0][2] = right.z;
	setup->camToWorld[1][0] = up.x;
	setup->camToWorld[1][1] = up.y;
	setup->camToWorld[1][2] = up.z;
	setup->camToWorld[2][0] = forward.x;
	setup->camToWorld[2][1] = forward.y;
	setup->camToWorld[2][2] = forward.z;

	setup->camToWorld[3][0] = cam->org.x;
	setup->camToWorld[3][1] = cam->org.y;
	setup->camToWorld[3][2] = cam->org.z;
	setup->camToWorld[3][3] = 1.;
}

void			init_cam(t_cam *cam, t_vec3 org, t_vec3 look_at)
{
	cam->org = org;
	cam->frt = normal_vect(vect_sub(look_at, org));
	cam->dwn = normal_vect(vect_mult(init_vec3(0.0, 1.0, 0.0), cam->frt));
	if (vect_mult_scale(cam->dwn, init_vec3(0.0, 0.0, 1.0)) > 0.0)
		cam->dwn = vect_scale(-1.0, cam->dwn);
	if (norme_vect(cam->dwn) == 0.0)
	{
		cam->dwn = normal_vect(vect_mult(init_vec3(1.0, 0.0, 0.0), cam->frt));
		if (vect_mult_scale(cam->dwn, init_vec3(0.0, 0.0, 1.0)) > 0.0)
			cam->dwn = vect_scale(-1.0, cam->dwn);
	}
	cam->rgt = normal_vect(vect_mult(cam->frt, cam->dwn));
}

static t_list	*ft_newcam(void)
{
	t_list		*cam; // changer cam pour list parce que pas tres clair

	if (!(cam = (t_list*)malloc(sizeof(t_list))) || \
			!(cam->content = (t_cam*)ft_memalloc(sizeof(t_cam))))
		return (NULL);
	cam->content_size = sizeof(t_cam);
	cam->next = NULL;
	return (cam);
}

static void		ft_cam_struct_pop(t_list *cam, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&CAM(cam)->org, ENVSTRUCT(env)->value); // cette fonction attend une string qui decrit un vecteur qui va peupler cam_pos, return ERROR si pas bon format
	else if (ft_strcmp(ENVSTRUCT(env)->name, "look_at") == 0)
		flag[1] = ft_getvectfromenv(&CAM(cam)->look_at, ENVSTRUCT(env)->value);
	CAM(cam)->num_arg++;
}

size_t			ft_cam(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*cam;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCAM))) // initialise un tableau de bool a ERROR, pour verifier que tout est bien formate a la fin
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCAM);
	ft_lstaddend(&SCN.cams, ft_newcam());
	cam = SCN.cams;
	while (cam->next)
		cam = cam->next;
	while (CAM(cam)->num_arg < NVARCAM && env && (env = env->next)) // je passe au node suivant, qui est sense etre cam_pos ou cam_dir
		ft_cam_struct_pop(cam, env, flag); // va trouver la variable correspondante au node (ici cam_pos ou cam_dir) et peuple cette variable + cherche si erreur
	if (ft_checkifallset(flag, NVARCAM) != OK) // ici si tout le tableau de flag est a OK, c'est que pas d'erreur
		return (setup->error = CAM_ERROR);
	SCN.num_cam++; // passe a la camera suivant si il y en a, permet en meme temps d'indiquer le nombre total de camera
	*list = env;
	return (OK);
}

// See: http://people.cs.clemson.edu/~dhouse/courses/405/notes/raycamera.pdf
//void			ft_setup_cam(t_setup *setup)
//{
//	int			cam_n;
//	t_vec3		u_x;
//	t_vec3		u_y;
//	t_vec3		c_0;
//
//	cam_n = -1;
//	while (++cam_n < (int)NCAM)
//	{
//		CAM[cam_n].focal_len = 360.; // gere l'ouverture du champ de vision
//		//ft_vec3vop_r (gere toutes les operations de vecteur sur vecteur et return le vecteur resultant)
//		//ft_vec3sop_r (gere toutes les operations de vecteur sur double et return le vecteur resultant)
//		c_0 = ft_vec3vop_r(CAM[cam_n].pos, ft_vec3sop_r(CAM[cam_n].dir, \
//					CAM[cam_n].focal_len, '*'), '+');
//		//printf("c_0 : %f, %f, %f\n", c_0.x, c_0.y, c_0.z);
//		u_x = ft_vec3unit(ft_vec3vop_r(CAM[cam_n].dir, \
//					ft_vec3_r(0., -1., 0.), 'c'));
//		u_y = ft_vec3vop_r(ft_vec3sop_r(CAM[cam_n].dir, -1.0, '*'), u_x, 'c');
//		CAM[cam_n].plane_center = c_0;
//		CAM[cam_n].plane_dirX = u_x;
//		CAM[cam_n].plane_dirY = u_y;
//		//	printf("CAM[cam_n] dirX : %f, %f, %f\nCAM[cam_n] dirY : %f, %f, %f\nCAM[cam_n] center : %f, %f, %f\n", \
//		//				CAM[cam_n].plane_dirX.x, CAM[cam_n].plane_dirX.y, CAM[cam_n].plane_dirX.z, \
//		//				CAM[cam_n].plane_dirY.x, CAM[cam_n].plane_dirY.y, CAM[cam_n].plane_dirY.z, \
//		//				CAM[cam_n].plane_center.x, CAM[cam_n].plane_center.y, CAM[cam_n].plane_center.z);
//	}
//}
