/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:05:50 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/19 16:30:53 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_getspheres(t_list **env, char *obj_str)
{
	char	*sphere;
	int		index;

	index = 0;
	while ((sphere = ft_getobjstr(obj_str, "sphere", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("sphere"), NULL));
		ft_getvaluetoenv(env, sphere, "center");
		ft_getvaluetoenv(env, sphere, "radius");
		ft_getmaterial(env, ft_getobjstr(sphere, "material", 0));
		free(sphere);
	}
}

void		ft_getplanes(t_list **env, char *obj_str)
{
	char	*plane;
	int		index;

	index = 0;
	while ((plane = ft_getobjstr(obj_str, "plane", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("plane"), NULL));
		ft_getvaluetoenv(env, plane, "normale");
		ft_getvaluetoenv(env, plane, "distance");
		ft_getmaterial(env, ft_getobjstr(plane, "material", 0));
		free(plane);
	}
}

void		ft_getcones(t_list **env, char *obj_str)
{
	char	*cone;
	int		index;

	index = 0;
	while ((cone = ft_getobjstr(obj_str, "cone", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("cone"), NULL));
		ft_getvaluetoenv(env, cone, "origin");
		ft_getvaluetoenv(env, cone, "direction");
		ft_getvaluetoenv(env, cone, "degres");
		ft_getmaterial(env, ft_getobjstr(cone, "material", 0));
		free(cone);
	}
}

void		ft_getcylindres(t_list **env, char *obj_str)
{
	char	*cylindre;
	int		index;

	index = 0;
	while ((cylindre = ft_getobjstr(obj_str, "cylindre", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("cylindre"), NULL));
		ft_getvaluetoenv(env, cylindre, "position");
		ft_getvaluetoenv(env, cylindre, "direction");
		ft_getvaluetoenv(env, cylindre, "radius");
		ft_getmaterial(env, ft_getobjstr(cylindre, "material", 0));
		free(cylindre);
	}
}

void		ft_gettorus(t_list **env, char *obj_str)
{
	char	*torus;
	int		index;

	index = 0;
	while ((torus = ft_getobjstr(obj_str, "torus", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("torus"), NULL));
		ft_getvaluetoenv(env, torus, "origin");
		ft_getvaluetoenv(env, torus, "direction");
		ft_getvaluetoenv(env, torus, "small_radius");
		ft_getvaluetoenv(env, torus, "big_radius");
		ft_getmaterial(env, ft_getobjstr(torus, "material", 0));
		free(torus);
	}
}

void		ft_getmoebius(t_list **env, char *obj_str)
{
	char	*moebius;
	int		index;

	index = 0;
	while ((moebius = ft_getobjstr(obj_str, "moebius", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("moebius"), NULL));
		ft_getvaluetoenv(env, moebius, "origin");
		ft_getvaluetoenv(env, moebius, "axe_x");
		ft_getvaluetoenv(env, moebius, "axe_y");
		ft_getvaluetoenv(env, moebius, "radius");
		ft_getvaluetoenv(env, moebius, "width");
		ft_getmaterial(env, ft_getobjstr(moebius, "material", 0));
		free(moebius);
	}
}
