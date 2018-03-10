/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:52:35 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/28 16:06:15 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		ft_getvaluetoenv(t_list **env, char *obj_str, const char *name)
{
	char	*value;

	if (name && (value = ft_getobjstr(obj_str, (char *)name, 0)))
		ft_lstaddend(env, ft_newenv(ft_strdup(name), value));
}

void		ft_getmaterial(t_list **env, char *mat_str)
{
	ft_getvaluetoenv(env, mat_str, "color");
	ft_getvaluetoenv(env, mat_str, "reflexion");
	ft_getvaluetoenv(env, mat_str, "refractive_index");
	ft_getvaluetoenv(env, mat_str, "transparency");
	free(mat_str);
}

t_bool		*ft_mat_struct_pop(t_list *form, t_list *env, t_bool *flag, \
		size_t n_flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[n_flag] = ft_getcolfromenv(&FORM(form)->mat.col, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "reflexion") == 0)
		flag[n_flag + 1] = ft_getdoublefromenv(&FORM(form)->mat.refl, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "refractive_index") == 0)
		flag[n_flag + 2] = ft_getdoublefromenv(&FORM(form)->mat.n, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "transparency") == 0)
		flag[n_flag + 3] = ft_getdoublefromenv(&FORM(form)->mat.trsp, \
				ENVSTRUCT(env)->value);
				// ICI SHOPER LA TEXTURE CORRESPONDANTE
				// TODO AAJOUTER DEFINES POUR LES TEXTURES
	FORM(form)->mat.text = 0;
	return (flag);
}
