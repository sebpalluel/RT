/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colorcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:07:12 by psebasti          #+#    #+#             */
/*   Updated: 2017/04/11 15:37:36 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_colorcpy(t_color *clr_from, t_color *clr_to)
{
	if (clr_from && clr_to)
	{
		clr_to->r = clr_from->r;
		clr_to->g = clr_from->g;
		clr_to->b = clr_from->b;
	}
}
