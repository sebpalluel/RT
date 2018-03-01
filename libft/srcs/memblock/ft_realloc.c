/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 01:06:13 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/01 17:05:25 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void				*ft_realloc(void *buff, size_t size, size_t n)
{
	char			*tmp;

	if ((tmp = (char*)ft_memalloc(size + n + 1)) == NULL)
		return (NULL);
	if ((char*)buff)
	{
		ft_strncpy(tmp, (char*)buff, size);
		free(buff);
	}
	return (tmp);
}
