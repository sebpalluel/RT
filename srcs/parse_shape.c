/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:05:50 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/20 19:21:15 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_getspheres(t_list **env, char *obj_str)
{
	char	*sphere;
	char	*scope;
	t_bool	get_val;

	get_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((sphere = ft_getobjstrn(&scope, "sphere")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("sphere"), NULL));
		ft_getvaluetoenv(env, sphere, "center", &get_val);
		ft_getvaluetoenv(env, sphere, "radius", &get_val);
		ft_getmaterial(env, ft_getobjstr(sphere, "material"));
		free(sphere);
		if (!get_val)
			get_st()->error = SPHERE_ERROR;
	}
}

void		ft_getplanes(t_list **env, char *obj_str)
{
	char	*plane;
	char	*scope;
	t_bool	get_val;

	get_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((plane = ft_getobjstrn(&scope, "plane")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("plane"), NULL));
		ft_getvaluetoenv(env, plane, "normale", &get_val);
		ft_getvaluetoenv(env, plane, "distance", &get_val);
		ft_getmaterial(env, ft_getobjstr(plane, "material"));
		free(plane);
		if (!get_val)
			get_st()->error = PLANE_ERROR;
	}
}

void		ft_getcones(t_list **env, char *obj_str)
{
	char	*cone;
	char	*scope;
	t_bool	get_val;

	get_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((cone = ft_getobjstrn(&scope, "cone")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("cone"), NULL));
		ft_getvaluetoenv(env, cone, "origin", &get_val);
		ft_getvaluetoenv(env, cone, "direction", &get_val);
		ft_getvaluetoenv(env, cone, "degres", &get_val);
		ft_getmaterial(env, ft_getobjstr(cone, "material"));
		free(cone);
		if (!get_val)
			get_st()->error = CONE_ERROR;
	}
}

void		ft_getcylindres(t_list **env, char *obj_str)
{
	char	*cylindre;
	char	*scope;
	t_bool	get_val;

	get_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((cylindre = ft_getobjstrn(&scope, "cylindre")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("cylindre"), NULL));
		ft_getvaluetoenv(env, cylindre, "position", &get_val);
		ft_getvaluetoenv(env, cylindre, "direction", &get_val);
		ft_getvaluetoenv(env, cylindre, "radius", &get_val);
		ft_getmaterial(env, ft_getobjstr(cylindre, "material"));
		free(cylindre);
		if (!get_val)
			get_st()->error = CYLINDRE_ERROR;
	}
}

void		ft_gettorus(t_list **env, char *obj_str)
{
	char	*torus;
	char	*scope;
	t_bool	get_val;

	get_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((torus = ft_getobjstrn(&scope, "torus")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("torus"), NULL));
		ft_getvaluetoenv(env, torus, "origin", &get_val);
		ft_getvaluetoenv(env, torus, "direction", &get_val);
		ft_getvaluetoenv(env, torus, "small_radius", &get_val);
		ft_getvaluetoenv(env, torus, "big_radius", &get_val);
		ft_getmaterial(env, ft_getobjstr(torus, "material"));
		free(torus);
		if (!get_val)
			get_st()->error = TORUS_ERROR;
	}
}

void		ft_getmoebius(t_list **env, char *obj_str)
{
	char	*moebius;
	char	*scope;
	t_bool	get_val;

	get_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((moebius = ft_getobjstrn(&scope, "moebius")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("moebius"), NULL));
		ft_getvaluetoenv(env, moebius, "origin", &get_val);
		ft_getvaluetoenv(env, moebius, "axe_x", &get_val);
		ft_getvaluetoenv(env, moebius, "axe_y", &get_val);
		ft_getvaluetoenv(env, moebius, "radius", &get_val);
		ft_getvaluetoenv(env, moebius, "width", &get_val);
		ft_getmaterial(env, ft_getobjstr(moebius, "material"));
		free(moebius);
		if (!get_val)
			get_st()->error = MOEBIUS_ERROR;
	}
}
