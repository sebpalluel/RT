/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:47:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/19 20:17:59 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_list			*ft_newform(void)
{
	t_list		*form;

	if (!(form = (t_list*)malloc(sizeof(t_list))) || \
			!(form->content = (t_forms*)ft_memalloc(sizeof(t_cam))))
		return (NULL);
	form->content_size = sizeof(t_forms);
	form->next = NULL;
	return (form);
}

//t_objsparam				*ft_objsparam(void)
//{
//	struct s_objsparam	*objs;
//
//	if (!(objs = ft_memalloc(sizeof(t_objsparam) * 2 + 1)))
//		return (NULL);
//	objs[SPH].paramfunc = ft_sphere_param;
//	// objs[PLN].paramfunc = ft_plane_param;
//	return (objs);
//}
//
//size_t					ft_getobjscount(t_setup *setup)
//{
//	return (NPLANE + NSPHERE);
//}
