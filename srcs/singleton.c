/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 21:09:13 by esuits            #+#    #+#             */
/*   Updated: 2018/02/27 14:14:39 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_func_col		*intersection(void)
{
	static t_func_col func[NUM_FORM] = {&intersec_sphere, &intersec_plan, \
		&intersec_cone, &intersec_cyl};

	return (func);
}

t_func_dble	*hit_shape(void)
{
	static t_func_dble func[NUM_FORM] = {&hit_sphere, &hit_plan, \
		&hit_cone, &hit_cyl};

	return (func);
}

t_func_vec3	*normal_shape(void)
{
	static t_func_vec3 func[NUM_FORM] = {&normal_sphere, &normal_plane, \
		&normal_cone, &normal_cyl};

	return (func);
}

t_setup					*get_st(void)
{
	static t_setup		setup;

	return (&setup);
}

t_parse_obj				*parse_obj(void)
{
	static t_parse_obj parse[NUM_OBJS] = {&ft_engine, &ft_cam, &ft_light\
	, &ft_plane, &ft_sphere, &ft_cone, &ft_cylindre};

	return (parse);
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
	validobjs[6] = "cylindre";
	return (validobjs);
}

#define NUM_TEXT 2
t_text **get_texture(void)
{
		static t_text *textures[NUM_TEXT];
		textures[0] = get_texture_datas("./textures/green400x400.bmp");
		textures[1] = get_texture_datas("./textures/tile4.bmp");
		return (textures);
}

t_func_uv_map	*uv_map(void)
{
	// valeur en dur a remplacé par num_form
	static	t_func_uv_map func[4] = {&uv_map_sph, &uv_map_pln, &uv_map_cone, &uv_map_cyl};

	return (func);
}
