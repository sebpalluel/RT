/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srttrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 17:38:31 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/03 12:27:48 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	length;
	char			*str;

	start = 0;
	end = 0;
	length = 0;
	if (s)
	{
		while (s[start] && ft_isspace(s[start]) == OK)
			start++;
		end = ft_strlen(s) - 1;
		while (s[start] && ft_isspace(s[end]) == OK)
			end--;
		length = end - start + 1;
		if (!(str = ft_strsub(s, start, length)))
			return (NULL);
		return (str);
	}
	return (NULL);
}
