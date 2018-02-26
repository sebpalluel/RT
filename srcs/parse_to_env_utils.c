/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_env_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:52:35 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 14:23:10 by psebasti         ###   ########.fr       */
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
	ft_getvaluetoenv(env, mat_str, "diffuse");
	ft_getvaluetoenv(env, mat_str, "specular");
}
