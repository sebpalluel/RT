/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:05:50 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/21 13:03:51 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_getspheres(t_list **env, char *obj_str)
{
	char	*sphere;
	char	*scope;
	t_bool	no_val;

	no_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((sphere = ft_getobjstrn(&scope, "sphere")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("sphere"), NULL));
		ft_getvaluetoenv(env, sphere, "center", &no_val);
		ft_getvaluetoenv(env, sphere, "radius", &no_val);
		ft_getmaterial(env, ft_getobjstr(sphere, "material"));
		free(sphere);
		if (no_val)
			get_st()->error = SPHERE_ERROR;
	}
	ft_strdel(&scope);
}

void		ft_getplanes(t_list **env, char *obj_str)
{
	char	*plane;
	char	*scope;
	t_bool	no_val;

	no_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((plane = ft_getobjstrn(&scope, "plane")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("plane"), NULL));
		ft_getvaluetoenv(env, plane, "normale", &no_val);
		ft_getvaluetoenv(env, plane, "distance", &no_val);
		ft_getmaterial(env, ft_getobjstr(plane, "material"));
		free(plane);
		if (no_val)
			get_st()->error = PLANE_ERROR;
	}
	ft_strdel(&scope);
}

void		ft_getcones(t_list **env, char *obj_str)
{
	char	*cone;
	char	*scope;
	t_bool	no_val;

	no_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((cone = ft_getobjstrn(&scope, "cone")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("cone"), NULL));
		ft_getvaluetoenv(env, cone, "origin", &no_val);
		ft_getvaluetoenv(env, cone, "direction", &no_val);
		ft_getvaluetoenv(env, cone, "degres", &no_val);
		ft_getmaterial(env, ft_getobjstr(cone, "material"));
		free(cone);
		if (no_val)
			get_st()->error = CONE_ERROR;
	}
	ft_strdel(&scope);
}

void		ft_getcylindres(t_list **env, char *obj_str)
{
	char	*cylindre;
	char	*scope;
	t_bool	no_val;

	no_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((cylindre = ft_getobjstrn(&scope, "cylindre")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("cylindre"), NULL));
		ft_getvaluetoenv(env, cylindre, "position", &no_val);
		ft_getvaluetoenv(env, cylindre, "direction", &no_val);
		ft_getvaluetoenv(env, cylindre, "radius", &no_val);
		ft_getmaterial(env, ft_getobjstr(cylindre, "material"));
		free(cylindre);
		if (no_val)
			get_st()->error = CYLINDRE_ERROR;
	}
	ft_strdel(&scope);
}

void		ft_getmoebius(t_list **env, char *obj_str)
{
	char	*moebius;
	char	*scope;
	t_bool	no_val;

	no_val = FALSE;
	scope = ft_strdup(obj_str);
	while ((moebius = ft_getobjstrn(&scope, "moebius")))
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("moebius"), NULL));
		ft_getvaluetoenv(env, moebius, "origin", &no_val);
		ft_getvaluetoenv(env, moebius, "axe_x", &no_val);
		ft_getvaluetoenv(env, moebius, "axe_y", &no_val);
		ft_getvaluetoenv(env, moebius, "radius", &no_val);
		ft_getvaluetoenv(env, moebius, "width", &no_val);
		ft_getmaterial(env, ft_getobjstr(moebius, "material"));
		free(moebius);
		if (no_val)
			get_st()->error = MOEBIUS_ERROR;
	}
	ft_strdel(&scope);
}
