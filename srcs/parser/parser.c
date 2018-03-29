/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 17:14:30 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/21 10:53:18 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void		ft_movescope(char **str, size_t len)
{
	char		*trunc_str;
	char		*tmp;

	tmp = *str;
	trunc_str = ft_strnew(ft_strlen(*str) - len);
	ft_memcpy(trunc_str, &str[0][len], ft_strlen(*str) - len);
	*str = trunc_str;
	ft_strdel(&tmp);
}

static void		ft_free(char *objstart, char *objend)
{
	if (objstart)
		ft_strdel(&objstart);
	if (objend)
		ft_strdel(&objend);
}

static char		*ft_extractobj(size_t len, char *from_begin, char *from_end)
{
	char		*objstr;

	if (from_end - (from_begin + len + 1) > 0)
	{
		if (!(objstr = ft_strnew(from_end - (from_begin + len) + 1)))
			return (NULL);
		ft_strncpy(objstr, from_begin + len, from_end - (from_begin + len));
		return (objstr);
	}
	return (NULL);
}

char			*ft_getobjstr(char *str, char *obj)
{
	char		*objstart;
	char		*objend;
	char		*from_begin;
	char		*from_end;
	char		*objstr;

	objstr = NULL;
	from_begin = NULL;
	from_end = NULL;
	objstart = ft_strjoinfree(ft_strdup("<"), ft_strjoin(obj, ">"), 0);
	objend = ft_strjoinfree(ft_strdup("</"), ft_strjoin(obj, ">"), 0);
	if (objstart && objend)
	{
		if (!(from_begin = ft_strstr(str, objstart)) || \
				!(from_end = ft_strstr(from_begin, objend)))
		{
			ft_free(objstart, objend);
			return (NULL);
		}
		objstr = ft_extractobj(ft_strlen(objstart), from_begin, from_end);
	}
	ft_free(objstart, objend);
	return (objstr);
}

char			*ft_getobjstrn(char **str, char *obj)
{
	char		*objstart;
	char		*objend;
	char		*from_begin;
	char		*from_end;
	char		*objstr;

	objstr = NULL;
	from_begin = NULL;
	from_end = NULL;
	objstart = ft_strjoinfree(ft_strdup("<"), ft_strjoin(obj, ">"), 0);
	objend = ft_strjoinfree(ft_strdup("</"), ft_strjoin(obj, ">"), 0);
	if (objstart && objend)
	{
		if (!(from_begin = ft_strstr(*str, objstart)) || \
				!(from_end = ft_strstr(from_begin, objend)))
		{
			ft_free(objstart, objend);
			return (NULL);
		}
		objstr = ft_extractobj(ft_strlen(objstart), from_begin, from_end);
		ft_movescope(str, from_end - *str);
	}
	ft_free(objstart, objend);
	return (objstr);
}

static t_list	*ft_envlistfromparse(t_setup *setup, char **parsed)
{
	t_list		*env;

	env = NULL;
	ft_getengine(&env, ENG_S);
	ft_getcams(&env, CAM_S);
	ft_getobjects(&env, OBJ_S);
	ft_getlights(setup, &env, LGT_S);
	ft_tabfree((void **)parsed);
	if (setup->error != OK)
	{
		ft_quit(setup);
		return (NULL);
	}
	else
		return (env);
}

t_list			*ft_parse_scn(t_setup *setup, char *file)
{
	char		*scene;
	char		**parsed;

	if (!(parsed = (char **)ft_memalloc(sizeof(char *) * 5)))
		return (NULL);
	if (!(scene = ft_getobjstr(file, "scene")))
		setup->error = SCN_ERROR;
	if (setup->error == OK && !(ENG_S = ft_getobjstr(scene, "engine")))
		setup->error = ENG_ERROR;
	if (setup->error == OK && !(CAM_S = ft_getobjstr(scene, "cameras")))
		setup->error = CAM_ERROR;
	LGT_S = ft_getobjstr(scene, "lights");
	if (setup->error == OK && !(OBJ_S = ft_getobjstr(scene, "objects")))
		setup->error = OBJ_ERROR;
	if (scene)
		free(scene);
	free(file);
	if (setup->error != OK)
	{
		ft_tabfree((void*)parsed);
		return (NULL);
	}
	return (ft_envlistfromparse(setup, parsed));
}