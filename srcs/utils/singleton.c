/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 21:09:13 by esuits            #+#    #+#             */
/*   Updated: 2018/03/31 16:21:58 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
//#include "./includes/rt.h"

t_func_col		*intersection(void)
{
	static t_func_col func[NUM_FORM] = {&intersec_sphere, &intersec_plan, \
		&intersec_cone, &intersec_cyl, &intersec_tor, &intersec_moe};

	return (func);
}

t_func_dble	*hit_shape(void)
{
	static t_func_dble func[NUM_FORM] = {&hit_sphere, &hit_plan, \
		&hit_cone, &hit_cyl, &hit_tor, &hit_moe};

	return (func);
}

t_func_vec3	*normal_shape(void)
{
	static t_func_vec3 func[NUM_FORM] = {&normal_sphere, &normal_plane, \
		&normal_cone, &normal_cyl, &normal_tor, &normal_moe};

	return (func);
}

t_parse_obj				*parse_obj(void)
{
	static t_parse_obj parse[NUM_OBJS] = {&ft_engine, &ft_cam, &ft_light\
		, &ft_plane, &ft_sphere, &ft_cone, &ft_cylindre, &ft_torus, \
			&ft_moebius};

	return (parse);
}

t_effects				*effects(void)
{
	static t_effects effect[NUM_PROC] = {&ft_marble, &ft_zebra\
		, &ft_wood, &ft_cloud, &ft_perlin, &ft_checker};

	return (effect);
}

t_postproc				*postprocess(void)
{
	static t_postproc postp[NUM_EFFECTS] = {&ft_sepia, &ft_cel_shading\
		, &ft_negative, &ft_blackandwhite, &ft_blur};

	return (postp);
}

void					put_usage(t_error e)
{
	static char			*tab[MAX_ERROR] = {
		"error: file doesn't exist or don't have the rights"
		"error: engine is not in the correct format",
		"error: light struct is not in the correct format",
		"error: plane struct is not in the correct format",
		"error: sphere struct is not in the correct format",
		"error: cone struct is not in the correct format",
		"error: cylindre struct is not in the correct format",
		"error: torus struct is not in the correct format",
		"error: moebius struct is not in the correct format",
		"error: cam struct is not in the correct format",
		"error: scene is not in the correct format",
		"error: objects are not in the correct format",
		"error: dim is not in the correct format [100;4000]",
		"error: texture not allowed for torus and moebius",
		"error: one of the xml struct is not in the correct format",
		"error: one of the material is not in the correct format",
		"error: generative struct is not in the correct format",
		"error: texture struct is not in the correct format"
	};

	ft_putendl(tab[e]);
}

char					**ft_validobjs(void)
{
	static char			*validobjs[NUM_OBJS] = {
		"engine",
		"camera",
		"light",
		"plane",
		"sphere",
		"cone",
		"cylindre",
		"torus",
		"moebius"
	};

	return (validobjs);
}

t_text **get_texture(void)
{
		static t_text *textures[NUM_TEXT];
		textures[0] = get_texture_datas("./textures/grillage.png");
		textures[1] = get_texture_datas("./textures/tile4.bmp");
		return (textures);
}

t_func_uv_map	*uv_map(void)
{
	// valeur en dur a remplacé par num_form
	static	t_func_uv_map func[4] = {&uv_map_sph, &uv_map_pln, &uv_map_cone, &uv_map_cyl};

	return (func);
}
