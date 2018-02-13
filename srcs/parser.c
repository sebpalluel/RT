/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 17:14:30 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/13 18:17:16 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static char	*ft_extractobj(size_t len, char *from_begin, char *from_end)
{
	char	*objstr;

	if (from_end - (from_begin + len + 1) > 0)
	{
		if (!(objstr = ft_strnew(from_end - (from_begin + len) + 1)))
			return (NULL);
		ft_strncpy(objstr, from_begin + len, from_end - (from_begin + len));
		return (objstr);
	}
	return (NULL);
}



//size_t		ft_getobjstartnum(char **from_begin, char *str, char *objstart)
//{
//	if (!*from_begin)
//		*from_begin = ft_strstr(str, objstart);
//	else
//		*from_begin = ft_strstr(*from_begin, objstart);
//	if (!*from_begin)
//		return (ERROR);
//
//	return (OK);
//}

char		*ft_getobjstr(char *str, char *obj, int num)
{
	char	*objstart;
	char	*objend;
	char	*from_begin;
	char	*from_end;
	char	*objstr;

	objstr = NULL;
	from_begin = NULL;
	objstart = ft_strjoinfree(ft_strdup("<"), ft_strjoin(obj, ">"), 0);
	objend = ft_strjoinfree(ft_strdup("</"), ft_strjoin(obj, ">"), 0);
	if (objstart && objend)
	{
		if (!(from_begin = ft_strstrn(str, objstart, num)) || \
				!(from_end = ft_strstr(from_begin, objend)))
			return (NULL);
		objstr = ft_extractobj(ft_strlen(objstart), from_begin, from_end);
	}
	ft_strdel(&objstart);
	ft_strdel(&objend);
	return (objstr);
}

t_list		*ft_envlistfromparse(t_setup *setup, char **parsed)
{
	t_list	*env;

	env = NULL;
	ft_getengine(&env, ENG_S);
	ft_getcams(&env, CAM_S);
	SETUP.error = OK;
	return (env);
}

t_list		*ft_parse_scn(t_setup *setup, char *file)
{
	char	*scene;
	char	**parsed;

	if (!(parsed = (char **)ft_memalloc(sizeof(char *) * 5)))
		return (NULL);
	if (!(scene = ft_getobjstr(file, "scene", 0)))
		SETUP.error = SCN_ERROR;
	if (SETUP.error == OK && !(ENG_S = ft_getobjstr(scene, "engine", 0)))
		SETUP.error = ENG_ERROR;
	if (SETUP.error == OK && !(CAM_S = ft_getobjstr(scene, "cameras", 0)))
		SETUP.error = CAM_ERROR;
	if (SETUP.error == OK && !(LGT_S = ft_getobjstr(scene, "lights", 0)))
		SETUP.error = LIGHT_ERROR;
	if (SETUP.error == OK && !(OBJ_S = ft_getobjstr(scene, "objects", 0)))
		SETUP.error = OBJ_ERROR;
	if (SETUP.error != OK)
		return (NULL);
	return (ft_envlistfromparse(setup, parsed));
	//((lights = ft_get_inner(scene, "lights")) != NULL) ?
	//	ft_get_lights(lights, ft_strlen(lights), e) :
	//	ft_putstr("There are no lights in your scene file.\n");
	//ft_set_config(config, e);
	//ft_set_camera(camera, e);
	//ft_set_objects(objects, e);
	//ft_free_all_dat_stuff((char **[5]){&lights, &scene, &camera, &objects,
	//										&config});
}
