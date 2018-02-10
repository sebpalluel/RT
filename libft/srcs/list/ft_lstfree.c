/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:20:24 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/07 23:07:55 by pciavald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstfree(t_list **lst)
{
	t_list	*ptr;

	ptr = *lst;
	while (*lst)
	{
		ptr = ptr->next;
		if ((*lst)->content != NULL)
			free((*lst)->content);
		free(*lst);
		*lst = ptr;
	}
	free(lst);
}
