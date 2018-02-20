/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:36 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/20 17:20:18 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			init_cam(t_cam *cam)
{
	cam->frt = normal_vect(vect_sub(cam->look_at, cam->org));
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
	t_list		*cam;

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
	init_cam(CAM(cam));
	SCN.num_cam++; // passe a la camera suivant si il y en a, permet en meme temps d'indiquer le nombre total de camera
	*list = env;
	return (OK);
}
