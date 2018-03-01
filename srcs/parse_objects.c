/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:50:02 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 14:22:27 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_getlights(t_setup *setup, t_list **env, char *light_str)
{
	char	*light;
	int		index;
	t_bool	no_lght;

	index = 0;
	no_lght = (light_str != NULL ? ERROR : OK);
	while ((light = ft_getobjstr(light_str, "light", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("light"), NULL));
		ft_getvaluetoenv(env, light, "type");
		ft_getvaluetoenv(env, light, "position");
		ft_getvaluetoenv(env, light, "color");
		no_lght = OK;
		free(light);
	}
	if (no_lght != OK)
		setup->error = LIGHT_ERROR;
}

void		ft_getcams(t_list **env, char *cam_str)
{
	char	*cam;
	int		index;

	index = 0;
	while ((cam = ft_getobjstr(cam_str, "camera", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("camera"), NULL));
		ft_getvaluetoenv(env, cam, "origin");
		ft_getvaluetoenv(env, cam, "look_at");
		free(cam);
	}
}

void		ft_getobjects(t_list **env, char *obj_str)
{
	ft_getspheres(env, obj_str);
	ft_getplanes(env, obj_str);
	ft_getcones(env, obj_str);
	ft_getcylindres(env, obj_str);
}

void		ft_getengine(t_list **env, char *eng_str)
{
	ft_lstaddend(env, ft_newenv(ft_strdup("engine"), NULL));
	ft_getvaluetoenv(env, eng_str, "width");
	ft_getvaluetoenv(env, eng_str, "height");
	ft_getvaluetoenv(env, eng_str, "refr_max");
	ft_getvaluetoenv(env, eng_str, "refl_max");
	ft_getvaluetoenv(env, eng_str, "amb_light");
}
