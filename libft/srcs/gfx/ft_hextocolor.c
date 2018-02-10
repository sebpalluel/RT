/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextocolor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:53:51 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:18:21 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_hextocolor(t_color *col, int hexvalue)
{
	if (col)
	{
		col->r = (unsigned char)((hexvalue >> 16) & 0xFF);
		col->g = (unsigned char)((hexvalue >> 8) & 0xFF);
		col->b = (unsigned char)((hexvalue) & 0xFF);
	}
}
