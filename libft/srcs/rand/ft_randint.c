/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 18:51:11 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/06 18:46:22 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

uintmax_t		ft_randint(size_t length)
{
	uintmax_t	rand;
	uintmax_t	ret;

	ret = 0;
	while (ft_intlen(ret) < length || ret == 0)
	{
		rand = ft_rand();
		rand = ft_hash32(rand);
		ret *= 10;
		ret += rand % 10;
	}
	return (ret);
}
