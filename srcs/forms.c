/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 16:27:54 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_list			*ft_newform(void)
{
	t_list		*form;

	if (!(form = (t_list*)malloc(sizeof(t_list))) || \
			!(form->content = (t_forms*)ft_memalloc(sizeof(t_forms))))
		return (NULL);
	form->content_size = sizeof(t_forms);
	form->next = NULL;
	return (form);
}
