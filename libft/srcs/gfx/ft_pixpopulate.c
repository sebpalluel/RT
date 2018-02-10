/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixpopulate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 15:10:43 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/11 15:11:03 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_pixpopulate(t_pix *to_pix, int x, int y, int z)
{
	if (to_pix)
	{
		to_pix->x = x;
		to_pix->y = y;
		to_pix->z = z;
	}
}
