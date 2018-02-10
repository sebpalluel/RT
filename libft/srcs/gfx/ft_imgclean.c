/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imgclean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:16:07 by psebasti          #+#    #+#             */
/*   Updated: 2017/05/19 15:49:38 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_imgclean(t_img *img, size_t width, size_t height)
{
	ft_bzero(img->image_addr, width * height * img->bbp / 8);
}
