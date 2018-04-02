/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 21:09:13 by esuits            #+#    #+#             */
/*   Updated: 2018/03/19 17:50:02 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_func_col		*intersection(void)
{
	static t_func_col func[NUM_FORM] = {&intersec_sphere, &intersec_plan,
		&intersec_cone, &intersec_cyl, &intersec_moe};

	return (func);
}

t_func_dble		*hit_shape(void)
{
	static t_func_dble func[NUM_FORM] = {&hit_sphere, &hit_plan,
		&hit_cone, &hit_cyl, &hit_moe};

	return (func);
}

t_func_vec3		*normal_shape(void)
{
	static t_func_vec3 func[NUM_FORM] = {&normal_sphere, &normal_plane,
		&normal_cone, &normal_cyl, &normal_moe};

	return (func);
}

t_setup			*get_st(void)
{
	static t_setup		setup;

	return (&setup);
}

t_parse_obj		*parse_obj(void)
{
	static t_parse_obj parse[NUM_OBJS] = {&ft_engine, &ft_cam, &ft_light
		, &ft_plane, &ft_sphere, &ft_cone, &ft_cylindre,
			&ft_moebius};

	return (parse);
}
