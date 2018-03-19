/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:52:35 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/19 19:24:09 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_getvaluetoenv(t_list **env, char *obj_str, const char *name)
{
	char	*value;

	if (name && (value = ft_getobjstr(obj_str, (char *)name, 0)))
		ft_lstaddend(env, ft_newenv(ft_strdup(name), value));
}

static void	ft_gettexture(t_list **env, char *text_str)
{
	if (text_str)
	{
		ft_getvaluetoenv(env, text_str, "texture_num");
		ft_getvaluetoenv(env, text_str, "size_x");
		ft_getvaluetoenv(env, text_str, "size_y");
		free(text_str);
	}
}

static void	ft_getgenerative(t_list **env, char *gen_str)
{
	if (gen_str)
	{
		ft_getvaluetoenv(env, gen_str, "mode");
		ft_getvaluetoenv(env, gen_str, "p_color");
		ft_getvaluetoenv(env, gen_str, "perlin_layers");
		ft_getvaluetoenv(env, gen_str, "perlin_frequency");
		ft_getvaluetoenv(env, gen_str, "perlin_persistance");
		free(gen_str);
	}
}

void		ft_getmaterial(t_list **env, char *mat_str)
{
	if (mat_str)
	{
		ft_getvaluetoenv(env, mat_str, "color");
		ft_getvaluetoenv(env, mat_str, "reflexion");
		ft_getvaluetoenv(env, mat_str, "refractive_index");
		ft_getvaluetoenv(env, mat_str, "transparency");
		ft_getvaluetoenv(env, mat_str, "texture_mode");
		ft_gettexture(env, ft_getobjstr(mat_str, "texture", 0));
		ft_getgenerative(env, ft_getobjstr(mat_str, "generative", 0));
		free (mat_str);
	}
}
