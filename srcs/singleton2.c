
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

	textures[0] = get_texture_datas("./textures/grillage.png");
	textures[1] = get_texture_datas("./textures/tile4.bmp");
	return (textures);
}

t_func_uv_map	*uv_map(void)
{
	static	t_func_uv_map func[4] = {&uv_map_sph, &uv_map_pln,
		&uv_map_cone, &uv_map_cyl};

	return (func);
}
