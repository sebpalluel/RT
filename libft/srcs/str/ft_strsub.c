/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srtsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:36:33 by psebasti          #+#    #+#             */
/*   Updated: 2016/11/12 00:17:19 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s && ((start + len) <= ft_strlen(s)))
	{
		if (!(str = ft_strnew(len)))
			return (NULL);
		else
			return (ft_strncpy(str, s + start, len));
	}
	return (NULL);
}
