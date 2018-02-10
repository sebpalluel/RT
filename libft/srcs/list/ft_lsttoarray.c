/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lsttoarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 14:29:57 by psebasti          #+#    #+#             */
/*   Updated: 2017/02/28 14:36:00 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_lsttoarray(t_list *lst)
{
	int		i;
	int		size;
	t_list	*next;
	void	**array;

	array = NULL;
	if (lst)
	{
		size = ft_lstlen(lst);
		if ((array = (void **)malloc(sizeof(void *) * (size + 1))))
		{
			i = 0;
			while (i < size)
			{
				array[i] = lst->content;
				next = lst->next;
				free(lst);
				lst = next;
				i++;
			}
			array[i] = NULL;
		}
	}
	return (array);
}
