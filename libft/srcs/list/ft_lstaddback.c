/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 16:11:53 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/24 17:56:49 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstaddback(t_list **alst, t_list *new)
{
	t_list	*curr;

	if (alst != NULL && new != NULL)
	{
		curr = *alst;
		if (curr != NULL)
		{
			while (curr->next != NULL)
				curr = curr->next;
			curr->next = new;
		}
		else
			*alst = new;
	}
}
