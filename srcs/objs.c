/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:47:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/14 18:55:15 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

char					**ft_validobjs(void) // ce qui contient tous les types d'objet qu'on gere pour le parsing
{
	char				**validobjs;

	if (!(validobjs = (char**)ft_memalloc(sizeof(char*) * NUM_OBJS + 1)))
		return (NULL);
	validobjs[0] = ft_strdup("engine");
	validobjs[1] = ft_strdup("camera");
	validobjs[2] = ft_strdup("light");
	validobjs[3] = ft_strdup("plane");
	validobjs[4] = ft_strdup("sphere");
	return (validobjs);
}

t_objsfunc				*ft_validfuncsptr(void)
{
	struct s_objsfunc	*objs;

	if (!(objs = ft_memalloc(sizeof(t_objsfunc) * NUM_OBJS + 1)))
		return (NULL);
	objs[0].builtinfunc = ft_engine;
	objs[1].builtinfunc = ft_cam; // voir les explications ici car c'est le meme process pour les autres
	objs[2].builtinfunc = ft_light;
	objs[3].builtinfunc = ft_plane;
	objs[4].builtinfunc = ft_sphere;
	return (objs);
}

t_objsparam				*ft_objsparam(void)
{
	struct s_objsparam	*objs;

	if (!(objs = ft_memalloc(sizeof(t_objsparam) * 2 + 1)))
		return (NULL);
	objs[SPH].paramfunc = ft_sphere_param;
	// objs[PLN].paramfunc = ft_plane_param;
	return (objs);
}

size_t					ft_getobjscount(t_setup *setup)
{
	return (NPLANE + NSPHERE);
}
