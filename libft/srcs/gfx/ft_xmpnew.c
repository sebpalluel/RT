/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xmpnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 15:07:38 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:20:07 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_img			*ft_xmpnew(void *mlx, char *xmp, size_t x, size_t y)
{
	t_img		*new;

	if (mlx)
	{
		if ((new = (t_img *)malloc(sizeof(t_img))))
		{
			if ((new->image = mlx_xpm_file_to_image(mlx, xmp, (int*)&x, \
							(int*)&y)))
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
