/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlxdelete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 21:08:06 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/03 15:46:19 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_mlxdelete(t_mlx *mlx, t_img *img)
{
	if (mlx && img)
	{
		if (mlx->win_ptr)
			mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		if (img->image_addr)
		{
			mlx_destroy_image(mlx->mlx_ptr, img->image);
			img->image = NULL;
			img->image_addr = NULL;
			free(img);
		}
		free(mlx);
	}
}
