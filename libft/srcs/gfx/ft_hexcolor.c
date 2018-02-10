/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexcolor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 13:55:43 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:18:47 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_color			*ft_hexcolor(int hexvalue)
{
	t_color		*col;

	col = ft_colornew((unsigned char)((hexvalue >> 16) & 0xFF),\
			(unsigned char)((hexvalue >> 8) & 0xFF),\
			(unsigned char)((hexvalue) & 0xFF));
	return (col);
}
