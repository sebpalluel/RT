/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 12:03:37 by psebasti          #+#    #+#             */
/*   Updated: 2017/12/01 16:42:49 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdelif2(t_list **head, void *to_cmpr, \
		int (*cmp)(void *, void *), void (*del)(void *, size_t))
{
	t_list	*lst_swap;
	t_list	*lst;

	lst_swap = NULL;
	lst = *head;
	while (lst->next && (*cmp)(lst->next->content, to_cmpr) != OK)
		lst = lst->next;
	if (lst)
	{
		if (lst->next && lst->next->next)
		{
			lst_swap = lst->next->next;
			ft_lstdelone(&lst->next, del);
			lst->next = lst_swap;
		}
		else if (lst->next)
		{
			ft_lstdelone(&lst->next, del);
			lst->next = NULL;
		}
	}
	*head = lst;
}

void		ft_lstdelif(t_list **head, void *to_cmpr, \
		int (*cmp)(void *, void *), void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*lst_swap;

	list = *head;
	if (*head && cmp && del)
	{
		if ((*cmp)(list->content, to_cmpr) == OK)
		{
			lst_swap = list->next;
			ft_lstdelone(&list, del);
			*head = lst_swap;
			list = *head;
		}
		while (list && list->next)
			ft_lstdelif2(&list, to_cmpr, cmp, del);
	}
}
