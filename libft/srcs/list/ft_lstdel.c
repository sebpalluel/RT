/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 16:12:37 by psebasti          #+#    #+#             */
/*   Updated: 2017/11/30 12:04:25 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*list_next;

	if (alst)
	{
		list = *alst;
		while (list)
		{
			list_next = list->next;
			if (del)
				(*del)(list->content, list->content_size);
			free(list);
			list = list_next;
		}
	}
	*alst = NULL;
}
