/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 21:32:13 by esuits            #+#    #+#             */
/*   Updated: 2018/04/04 17:26:25 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_effects		*effects(void)
{
	static t_effects effect[NUM_PROC] = {&ft_marble, &ft_zebra\
		, &ft_wood, &ft_cloud, &ft_perlin, &ft_checker};

	return (effect);
}

t_postproc		*postprocess(void)
{
	static t_postproc postp[NUM_EFFECTS] = {&ft_sepia, &ft_cel_shading\
		, &ft_negative, &ft_blackandwhite, &ft_blur};

	return (postp);
}

char			**ft_validobjs(void)
{
	static char			*validobjs[NUM_OBJS];

	validobjs[0] = "engine";
	validobjs[1] = "camera";
	validobjs[2] = "light";
	validobjs[3] = "plane";
	validobjs[4] = "sphere";
	validobjs[5] = "cone";
	validobjs[6] = "cylindre";
	validobjs[7] = "moebius";
	return (validobjs);
}

t_text			**get_texture(void)
{
	static t_text *textures[NUM_TEXT];

	textures[0] = get_texture_datas("./textures/mosaique.png");
	textures[1] = get_texture_datas("./textures/metal.jpg");
	textures[2] = get_texture_datas("./textures/brick.jpg");
	textures[3] = get_texture_datas("./textures/wood.jpg");
	textures[4] = get_texture_datas("./textures/stainedGlass1.png");
	textures[5] = get_texture_datas("./textures/tilesStainedGlass.png");
	textures[6] = get_texture_datas("./textures/anvil_base.png");
	textures[7] = get_texture_datas("./textures/ice_packed.png");
	textures[8] = get_texture_datas("./textures/log_birch_top.png");
	textures[9] = get_texture_datas("./textures/planks_oak.png");
	textures[10] = get_texture_datas("./textures/prismarine_bricks.png");
	textures[11] = get_texture_datas("./textures/quartz_block_bottom.png");
	textures[12] = get_texture_datas("./textures/stone_diorite.png");
	textures[13] = get_texture_datas("./textures/stone_andesite.png");
	return (textures);
}

t_func_uv_map	*uv_map(void)
{
	static	t_func_uv_map func[4] = {&uv_map_sph, &uv_map_pln,
		&uv_map_cone, &uv_map_cyl};

	return (func);
}
