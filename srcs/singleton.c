/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 21:09:13 by esuits            #+#    #+#             */
/*   Updated: 2018/02/23 15:40:12 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_setup					*get_st(void)
{
	static t_setup		setup;

	return (&setup);
}

t_parse_obj				*parse_obj(void)
{
	static t_parse_obj	parse[NUM_OBJS] = {&ft_engine, &ft_cam, &ft_light\
		, &ft_plane, &ft_sphere, &ft_cone, &ft_cldre};

	return (parse);
}

t_param					*param(void)
{
	static t_param param_ret[4] = {&ft_sphere_param, &ft_plane_param, \
		&ft_cone_intersect, &ft_cldre_intersect};

	return (param_ret);
}

char					**ft_validobjs(void)
{
	static char			*validobjs[NUM_OBJS];

	validobjs[0] = "engine";
	validobjs[1] = "camera";
	validobjs[2] = "light";
	validobjs[3] = "plane";
	validobjs[4] = "sphere";
	validobjs[5] = "cone";
	validobjs[6] = "cylindre";
	return (validobjs);
}
