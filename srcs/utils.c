/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:59:10 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/12 17:17:41 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_put_pixel(t_setup *setup, int x, int y, int color)
{
	int			*tmp;
	size_t		index;

	if (y >= (int)SCN.height || x >= (int)SCN.width || x < 0 || y < 0)
		return ;
	index = (y * SCN.width) * (SCN.img[SCN.effect]->bbp >> 3) \
			+ x * (SCN.img[SCN.effect]->bbp >> 3);
	tmp = (int *)&SCN.img[SCN.effect]->image_addr[index];
	*tmp = color;
}
