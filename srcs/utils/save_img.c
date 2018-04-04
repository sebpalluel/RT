/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 17:34:04 by psebasti          #+#    #+#             */
/*   Updated: 2018/04/04 19:09:52 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

static t_bool		put_header(t_scene scn, int fd)
{
	char			*width;
	char			*height;

	width = ft_itoa(scn.width);
	height = ft_itoa(scn.height);
	if (!width || !height)
		return (ERROR);
	write(fd, "P6\n", 3);
	write(fd, width, ft_strlen(width));
	write(fd, " ", 1);
	write(fd, height, ft_strlen(height));
	write(fd, "\n255\n", 5);
	free(width);
	free(height);
	return (OK);
}

char				*ft_savename(const char *name, size_t counter)
{
	char			*ret;

	ret = ft_strjoinfree((char*)name, ft_itoa(counter), 2);
	ret = ft_strjoinfree(ret, ft_strdup(".ppm"), 0);
	return (ret);
}

void				ft_saveimg(t_scene scn, char *name)
{
	int				fd;
	int				xy[2];
	size_t			b;
	t_img			*img;

	img = scn.img[scn.effect];
	if (name && (fd = open(name, O_CREAT | O_TRUNC | O_WRONLY, 0755)) >= 2 &&
			put_header(scn, fd) == OK)
	{
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
