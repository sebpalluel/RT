/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:33:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 17:29:07 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/rt.h"

t_list			*ft_new_p_env(char *name, char *value)
{
	t_list		*p_env;

	if (!(p_env = (t_list*)malloc(sizeof(t_list))) || \
			!(p_env->content = (t_p_env*)ft_memalloc(sizeof(t_p_env))))
		return (NULL);
	p_env->content_size = sizeof(t_p_env);
	p_env->next = NULL;
	P_ENV(p_env)->name = name;
	if (value)
		P_ENV(p_env)->value = value;
	else
		P_ENV(p_env)->value = ft_strdup("");
	if (!P_ENV(p_env)->name || !P_ENV(p_env)->value)
		return (NULL);
	return (p_env);
}

void		ft_delenvnode(void *content, size_t size)
{
	(void)size;
	if (((t_env*)(content))->name)
		free(((t_env*)(content))->name);
	if (((t_env*)(content))->value)
		free(((t_env*)(content))->value);
	free(content);
}

void		ft_dellistelem(void *content, size_t size)
{
	(void)size;
	if (content)
		free(content);
}
