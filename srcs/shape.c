/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 16:47:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/29 16:28:26 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

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
