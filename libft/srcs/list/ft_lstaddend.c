/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:06:28 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/30 15:30:40 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddend(t_list **alst, t_list *elem)
{
	t_list	*ptr;

	ptr = *alst;
	if (alst != NULL && *alst == NULL)
		*alst = elem;
	else
	{
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = elem;
	}
}
