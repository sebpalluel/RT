/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/12 17:14:30 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 22:08:34 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

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
