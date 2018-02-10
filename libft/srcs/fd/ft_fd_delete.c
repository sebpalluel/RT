/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_delete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 14:30:25 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/06 14:37:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_fd_delete(t_fd *fd)
{
	if (fd)
	{
		if (fd->name)
			free(fd->name);
		if (fd->path)
			free(fd->path);
		free(fd);
	}
}
