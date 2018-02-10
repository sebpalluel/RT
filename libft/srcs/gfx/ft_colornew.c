/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colornew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:51:55 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:17:19 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_color			*ft_colornew(unsigned char r, unsigned char g, \
		unsigned char b)
{
	t_color		*col;

	if ((col = (t_color*)malloc(sizeof(t_color))))
	{
		col->r = r;
		col->g = g;
		col->b = b;
	}
	return (col);
}
