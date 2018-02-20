/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 21:09:13 by esuits            #+#    #+#             */
/*   Updated: 2018/02/19 20:27:23 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

//t_func_col		*intersection(void)
//{
//	static t_func_col func[3] = {&intersec_sphere, &intersec_plan, &intersec_cone};
//	return (func);
//}
//
//t_func_double	*hit_shape(void)
//{
//	static t_func_double func[3] = {&hit_sphere, &hit_plan, &hit_cone};
//	return (func);
//}
//
t_setup					*get_st(void)
{
	static t_setup		setup;

	return (&setup);
}

t_parse_obj				*parse_obj(void)
{
	static t_parse_obj parse[NUM_OBJS] = {&ft_engine, &ft_cam, &ft_light\
	, &ft_plane, &ft_sphere, &ft_cone};

	return (parse);
}

t_param				*param(void)
{
	static t_param param_ret[3] = {&ft_sphere_param, &ft_plane_param, &ft_cone_intersect};

	return (param_ret);
}

char					**ft_validobjs(void) // ce qui contient tous les types d'objet qu'on gere pour le parsing
{
	static char			*validobjs[NUM_OBJS];

	validobjs[0] = "engine";
	validobjs[1] = "camera";
	validobjs[2] = "light";
	validobjs[3] = "plane";
	validobjs[4] = "sphere";
	validobjs[5] = "cone";
	return (validobjs);
}
