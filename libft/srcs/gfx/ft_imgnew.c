/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imgnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 14:18:28 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:19:26 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_img				*ft_imgnew(void *mlx, size_t x, size_t y)
{
	t_img		*new;

	if (mlx)
	{
		if ((new = (t_img *)malloc(sizeof(t_img))))
		{
			if ((new->image = mlx_new_image(mlx, x, y)))
			{
				if ((new->image_addr = mlx_get_data_addr(new->image, \
								&(new->bbp), &(new->size_x), &(new->endian))))
					return (new);
			}
		}
		ft_imgdel(new, mlx);
	}
	return (NULL);
}
