/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:52:35 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/21 10:56:09 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_getvaluetoenv(t_list **env, char *obj_str, const char *name,
		t_bool *no_val)
{
	char		*value;

	if (name && (value = ft_getobjstr(obj_str, (char *)name)))
		ft_lstaddend(env, ft_newenv(ft_strdup(name), value));
	else
		*no_val = TRUE;
}

static t_bool	ft_gettexture(t_list **env, char *text_str)
{
	t_bool		no_val;

	no_val = FALSE;
	if (text_str)
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("texture_mode"), ft_strdup("1")));
		ft_getvaluetoenv(env, text_str, "texture_num", &no_val);
		ft_getvaluetoenv(env, text_str, "size_x", &no_val);
		ft_getvaluetoenv(env, text_str, "size_y", &no_val);
		free(text_str);
		if (no_val)
			get_st()->error = TEX_ERROR;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	ft_getgenerative(t_list **env, char *gen_str)
{
	t_bool		no_val;

	no_val = FALSE;
	if (gen_str)
	{
		ft_lstaddend(env, ft_newenv(ft_strdup("texture_mode"), ft_strdup("2")));
		ft_getvaluetoenv(env, gen_str, "mode", &no_val);
		ft_getvaluetoenv(env, gen_str, "p_color", &no_val);
		ft_getvaluetoenv(env, gen_str, "perlin_layers", &no_val);
		ft_getvaluetoenv(env, gen_str, "perlin_frequency", &no_val);
		ft_getvaluetoenv(env, gen_str, "perlin_persistance", &no_val);
		free(gen_str);
		if (no_val)
			get_st()->error = GEN_ERROR;
		return (TRUE);
	}
	return (FALSE);
}

void			ft_getmaterial(t_list **env, char *mat_str)
{
	t_bool	no_val;
	t_bool	get_tex;
	t_bool	get_gen;

	no_val = FALSE;
	if (mat_str)
	{
		ft_getvaluetoenv(env, mat_str, "color", &no_val);
		ft_getvaluetoenv(env, mat_str, "reflexion", &no_val);
		ft_getvaluetoenv(env, mat_str, "refractive_index", &no_val);
		ft_getvaluetoenv(env, mat_str, "transparency", &no_val);
		get_tex = ft_gettexture(env, ft_getobjstr(mat_str, "texture"));
		get_gen = ft_getgenerative(env, ft_getobjstr(mat_str, "generative"));
		if (!get_tex && !get_gen)
		ft_lstaddend(env, ft_newenv(ft_strdup("texture_mode"), ft_strdup("0")));
		free (mat_str);
		if (no_val || (get_gen && get_tex))
			get_st()->error = MAT_ERROR;
	}
}
