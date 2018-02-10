/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 17:05:46 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/12 13:35:41 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_color(t_color *clr, \
		unsigned char r, unsigned char g, unsigned char b)
{
	clr->r = r;
	clr->g = g;
	clr->b = b;
}
