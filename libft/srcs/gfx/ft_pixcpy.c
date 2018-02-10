/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:10:41 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/11 18:03:55 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_pixcpy(t_pix *pix_from, t_pix *pix_to)
{
	if (pix_from && pix_to)
	{
		pix_to->x = pix_from->x;
		pix_to->y = pix_from->y;
		pix_to->z = pix_from->z;
	}
}
