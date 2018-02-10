/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 17:11:51 by psebasti          #+#    #+#             */
/*   Updated: 2016/11/22 20:01:23 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int u_n;

	u_n = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		u_n = -n;
	}
	if (u_n >= 10)
	{
		ft_putnbr_fd(u_n / 10, fd);
		ft_putnbr_fd(u_n % 10, fd);
	}
	else
		ft_putchar_fd(u_n + '0', fd);
}
