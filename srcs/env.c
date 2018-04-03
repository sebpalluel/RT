/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:33:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/03 21:28:16 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_list			*ft_newenv(char *name, char *value)
{
	t_list		*env; // changer env pour list parce que pas tres clair

	if (!(env = (t_list*)malloc(sizeof(t_list))) || \
			!(env->content = (t_env*)ft_memalloc(sizeof(t_env))))
		return (NULL);
	env->content_size = sizeof(t_env);
	env->next = NULL;
	ENVSTRUCT(env)->name = name;
	if (value)
		ENVSTRUCT(env)->value = value;
	else
		ENVSTRUCT(env)->value = ft_strdup("");
	if (!ENVSTRUCT(env)->name || !ENVSTRUCT(env)->value)
		return (NULL);
	return (env);
}


t_list			*ft_newshape(void)
{
	t_list		*form;

	if (!(form = (t_list*)malloc(sizeof(t_list))) || \
			!(form->content = (t_shape*)ft_memalloc(sizeof(t_shape))))
		return (NULL);
	form->content_size = sizeof(t_shape);
	form->next = NULL;
	return (form);
}
