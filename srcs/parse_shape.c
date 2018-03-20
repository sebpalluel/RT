/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:05:50 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/20 18:10:49 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_getspheres(t_list **env, char *obj_str)
{
	char	*sphere;
	int		index;
	t_bool	get_val;

	index = 0;
	get_val = FALSE;
	while ((sphere = ft_getobjstr(obj_str, "sphere", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("sphere"), NULL));
		ft_getvaluetoenv(env, sphere, "center", &get_val);
		ft_getvaluetoenv(env, sphere, "radius", &get_val);
		ft_getmaterial(env, ft_getobjstr(sphere, "material", 0));
		free(sphere);
		if (!get_val)
			get_st()->error = SPHERE_ERROR;
	}
}

void		ft_getplanes(t_list **env, char *obj_str)
{
	char	*plane;
	int		index;
	t_bool	get_val;

	index = 0;
	get_val = FALSE;
	while ((plane = ft_getobjstr(obj_str, "plane", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("plane"), NULL));
		ft_getvaluetoenv(env, plane, "normale", &get_val);
		ft_getvaluetoenv(env, plane, "distance", &get_val);
		ft_getmaterial(env, ft_getobjstr(plane, "material", 0));
		free(plane);
		if (!get_val)
			get_st()->error = PLANE_ERROR;
	}
}

void		ft_getcones(t_list **env, char *obj_str)
{
	char	*cone;
	int		index;
	t_bool	get_val;

	index = 0;
	get_val = FALSE;
	while ((cone = ft_getobjstr(obj_str, "cone", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("cone"), NULL));
		ft_getvaluetoenv(env, cone, "origin", &get_val);
		ft_getvaluetoenv(env, cone, "direction", &get_val);
		ft_getvaluetoenv(env, cone, "degres", &get_val);
		ft_getmaterial(env, ft_getobjstr(cone, "material", 0));
		free(cone);
		if (!get_val)
			get_st()->error = CONE_ERROR;
	}
}

void		ft_getcylindres(t_list **env, char *obj_str)
{
	char	*cylindre;
	int		index;
	t_bool	get_val;

	index = 0;
	get_val = FALSE;
	while ((cylindre = ft_getobjstrn(&obj_str, "cylindre", 0)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("cylindre"), NULL));
		ft_getvaluetoenv(env, cylindre, "position", &get_val);
		ft_getvaluetoenv(env, cylindre, "direction", &get_val);
		ft_getvaluetoenv(env, cylindre, "radius", &get_val);
		ft_getmaterial(env, ft_getobjstr(cylindre, "material", 0));
		free(cylindre);
		if (!get_val)
			get_st()->error = CYLINDRE_ERROR;
	}
}

void		ft_gettorus(t_list **env, char *obj_str)
{
	char	*torus;
	int		index;
	t_bool	get_val;

	index = 0;
	get_val = FALSE;
	while ((torus = ft_getobjstr(obj_str, "torus", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("torus"), NULL));
		ft_getvaluetoenv(env, torus, "origin", &get_val);
		ft_getvaluetoenv(env, torus, "direction", &get_val);
		ft_getvaluetoenv(env, torus, "small_radius", &get_val);
		ft_getvaluetoenv(env, torus, "big_radius", &get_val);
		ft_getmaterial(env, ft_getobjstr(torus, "material", 0));
		free(torus);
		if (!get_val)
			get_st()->error = TORUS_ERROR;
	}
}

void		ft_getmoebius(t_list **env, char *obj_str)
{
	char	*moebius;
	int		index;
	t_bool	get_val;

	index = 0;
	get_val = FALSE;
	while ((moebius = ft_getobjstr(obj_str, "moebius", index++)))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("moebius"), NULL));
		ft_getvaluetoenv(env, moebius, "origin", &get_val);
		ft_getvaluetoenv(env, moebius, "axe_x", &get_val);
		ft_getvaluetoenv(env, moebius, "axe_y", &get_val);
		ft_getvaluetoenv(env, moebius, "radius", &get_val);
		ft_getvaluetoenv(env, moebius, "width", &get_val);
		ft_getmaterial(env, ft_getobjstr(moebius, "material", 0));
		free(moebius);
		if (!get_val)
			get_st()->error = MOEBIUS_ERROR;
	}
}
