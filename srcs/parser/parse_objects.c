/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:50:02 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 17:09:04 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rt.h"

void		ft_getlights(t_scene *scn, t_list **env, char *light_str)
{
	char	*light;
	char	*scope;
	t_bool	no_val;

	no_val = FALSE;
	scope = ft_strdup(light_str);
	while ((light = ft_getobjstrn(&scope, "light")))
	{
		ft_lstaddend(env, ft_new_p_env(ft_strdup("light"), NULL));
		ft_getvaluetoenv(env, light, "type", &no_val);
		ft_getvaluetoenv(env, light, "position", &no_val);
		ft_getvaluetoenv(env, light, "color", &no_val);
		free(light);
		if (no_val)
			scn->error = LIGHT_ERROR;
	}
	ft_strdel(&scope);
}

void		ft_getcams(t_scene *scn, t_list **env, char *cam_str)
{
	char	*cam;
	char	*scope;
	t_bool	no_val;

	no_val = FALSE;
	scope = ft_strdup(cam_str);
	while ((cam = ft_getobjstrn(&scope, "camera")))
	{
		ft_lstaddend(env, ft_new_p_env(ft_strdup("camera"), NULL));
		ft_getvaluetoenv(env, cam, "origin", &no_val);
		ft_getvaluetoenv(env, cam, "look_at", &no_val);
		free(cam);
		if (no_val)
			scn->error = CAM_ERROR;
	}
	ft_strdel(&scope);
}

void		ft_getobjects(t_scene *scn, t_list **env, char *obj_str)
{
	ft_getspheres(scn, env, obj_str);
	ft_getplanes(scn, env, obj_str);
	ft_getcones(scn, env, obj_str);
	ft_getcylindres(scn, env, obj_str);
	ft_gettorus(scn, env, obj_str);
	ft_getmoebius(scn, env, obj_str);
}

void		ft_getengine(t_scene *scn, t_list **env, char *eng_str)
{
	t_bool	no_val;

	no_val = FALSE;
	ft_lstaddend(env, ft_new_p_env(ft_strdup("engine"), NULL));
	ft_getvaluetoenv(env, eng_str, "width", &no_val);
	ft_getvaluetoenv(env, eng_str, "height", &no_val);
	ft_getvaluetoenv(env, eng_str, "refr_max", &no_val);
	ft_getvaluetoenv(env, eng_str, "refl_max", &no_val);
	ft_getvaluetoenv(env, eng_str, "amb_light", &no_val);
	if (no_val)
		scn->error = ENG_ERROR;
}
