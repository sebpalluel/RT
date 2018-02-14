/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:05:50 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/14 11:33:27 by psebasti         ###   ########.fr       */
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
		ft_getvaluetoenv(env, planes, "normx");
		ft_getvaluetoenv(env, planes, "normy");
		ft_getvaluetoenv(env, planes, "normz");
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
