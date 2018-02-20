/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 17:05:46 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/19 16:24:57 by psebasti         ###   ########.fr       */
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
