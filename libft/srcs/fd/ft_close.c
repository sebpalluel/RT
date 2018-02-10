/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 20:25:38 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:14:41 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_close(t_fd *fd)
{
	if (!fd || (fd->path == NULL && fd->name == NULL))
		return (-1);
	free(fd->path);
	free(fd->name);
	if (close(fd->fd) == -1)
		return (-1);
	return (0);
}
