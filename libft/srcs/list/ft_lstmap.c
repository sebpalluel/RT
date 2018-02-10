/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:13:19 by psebasti          #+#    #+#             */
/*   Updated: 2016/11/23 15:14:05 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *tmp_list;
	t_list *out_list;

	if (!lst)
		return (NULL);
	out_list = f(lst);
	tmp_list = out_list;
	while (lst->next)
	{
		tmp_list->next = f(lst->next);
		tmp_list = tmp_list->next;
		lst = lst->next;
	}
	return (out_list);
}
