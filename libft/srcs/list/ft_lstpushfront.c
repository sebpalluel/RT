/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushfront.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 18:39:43 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/18 18:41:56 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstpushfront(t_list **alst, void *data, size_t content_size)
{
	t_list	*new_lst;

	if (alst != NULL)
	{
		new_lst = ft_lstnew(data, content_size);
		if (new_lst == NULL)
			return (NULL);
		ft_lstaddfront(alst, new_lst);
		return (new_lst);
	}
	return (NULL);
}
