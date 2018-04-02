/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 17:34:04 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/02 17:38:08 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static void			put_header(t_scene scn, int fd)
{
	write(fd, "P6\n", 3);
	write(fd, ft_itoa(scn.width), ft_strlen(ft_itoa(scn.width)));
	write(fd, " ", 1);
	write(fd, ft_itoa(scn.height), ft_strlen(ft_itoa(scn.height)));
	write(fd, "\n255\n", 5);
}

void				ft_saveimg(t_scene scn, char *name)
{
	int				fd;
	int				xy[2];
	size_t			b;
	t_img			*img;

	img = scn.img[scn.effect];
	if ((fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0755)) >= 2)
	{
		put_header(scn, fd);
		xy[1] = -1;
		while (++xy[1] < (int)scn.height)
		{
			xy[0] = -1;
			while (++xy[0] < (int)scn.width)
			{
				b = (xy[1] * scn.width) * (img->bbp >> 3) \
					+ xy[0] * (img->bbp >> 3);
				write(fd, &img->image_addr[b + 2], 1);
				write(fd, &img->image_addr[b + 1], 1);
				write(fd, &img->image_addr[b + 0], 1);
			}
		}
		close(fd);
	}
}
