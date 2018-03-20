/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:52:35 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/20 19:32:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_getvaluetoenv(t_list **env, char *obj_str, const char *name, \
		t_bool *no_val)
{
	char	*value;

	if (get_st()->error == OK && \
			name && (value = ft_getobjstr(obj_str, (char *)name)))
		ft_lstaddend(env, ft_newenv(ft_strdup(name), value));
	else
		*no_val = TRUE;
}

static void	ft_gettexture(t_list **env, char *text_str)
{
	t_bool	no_val;

	no_val = FALSE;
	if (text_str)
	{
		ft_getvaluetoenv(env, text_str, "texture_num", &no_val);
		ft_getvaluetoenv(env, text_str, "size_x", &no_val);
		ft_getvaluetoenv(env, text_str, "size_y", &no_val);
		free(text_str);
		if (no_val)
			get_st()->error = TEX_ERROR;
	}
}

static void	ft_getgenerative(t_list **env, char *gen_str)
{
	t_bool	no_val;

	no_val = FALSE;
	if (gen_str)
	{
		ft_getvaluetoenv(env, gen_str, "mode", &no_val);
		ft_getvaluetoenv(env, gen_str, "p_color", &no_val);
		ft_getvaluetoenv(env, gen_str, "perlin_layers", &no_val);
		ft_getvaluetoenv(env, gen_str, "perlin_frequency", &no_val);
		ft_getvaluetoenv(env, gen_str, "perlin_persistance", &no_val);
		free(gen_str);
		if (no_val)
			get_st()->error = GEN_ERROR;
	}
}

void			ft_getmaterial(t_list **env, char *mat_str)
{
	t_bool	no_val;

	no_val = FALSE;
	if (mat_str)
	{
		ft_getvaluetoenv(env, mat_str, "color", &no_val);
		ft_getvaluetoenv(env, mat_str, "reflexion", &no_val);
		ft_getvaluetoenv(env, mat_str, "refractive_index", &no_val);
		ft_getvaluetoenv(env, mat_str, "transparency", &no_val);
		ft_getvaluetoenv(env, mat_str, "texture_mode", &no_val);
		ft_gettexture(env, ft_getobjstr(mat_str, "texture"));
		ft_getgenerative(env, ft_getobjstr(mat_str, "generative"));
		free (mat_str);
		if (no_val)
			get_st()->error = MAT_ERROR;
	}
}
