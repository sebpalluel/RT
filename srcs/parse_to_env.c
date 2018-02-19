/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:05:50 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/19 17:15:30 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_getvaluetoenv(t_list **env, char *obj_str, const char *name)
{
	char	*value;

	if (name && (value = ft_getobjstr(obj_str, (char *)name, 0)))
		ft_lstaddend(env, ft_newenv(ft_strdup(name), value));
}

void		ft_getmaterial(t_list **env, char *mat_str)
{
	ft_getvaluetoenv(env, mat_str, "color");
	ft_getvaluetoenv(env, mat_str, "diffuse");
	ft_getvaluetoenv(env, mat_str, "specular");

}

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
		ft_getvaluetoenv(env, light, "intensity");
		ft_getvaluetoenv(env, light, "radius");
		ft_getvaluetoenv(env, light, "fallof");
		ft_getvaluetoenv(env, light, "focal_len");
		ft_getvaluetoenv(env, light, "direction");
		no_lght = OK;
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
		ft_getvaluetoenv(env, cam, "position");
		ft_getvaluetoenv(env, cam, "direction");
		ft_getvaluetoenv(env, cam, "focal_len");
	}
}

void		ft_getspheres(t_list **env, char *obj_str)
{
	char	*sphere;
	int		index;

	index = 0;
	while ((sphere = ft_getobjstr(obj_str, "sphere", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("sphere"), NULL));
		ft_getvaluetoenv(env, sphere, "position");
		ft_getvaluetoenv(env, sphere, "radius");
		ft_getmaterial(env, ft_getobjstr(sphere, "material", 0));
	}
}

void		ft_getplanes(t_list **env, char *obj_str)
{
	char	*planes;
	int		index;

	index = 0;
	while ((planes = ft_getobjstr(obj_str, "planes", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("planes"), NULL));
		ft_getvaluetoenv(env, planes, "position");
		ft_getvaluetoenv(env, planes, "norm");
		ft_getmaterial(env, ft_getobjstr(planes, "material", 0));
	}
}

void		ft_getobjects(t_list **env, char *obj_str)
{
	ft_getspheres(env, obj_str);
	ft_getplanes(env, obj_str);
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
