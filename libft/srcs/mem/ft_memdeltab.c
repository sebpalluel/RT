/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdeltab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 14:59:32 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/02 19:22:06 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_memdeltab(void *tab, size_t dimension)
{
	int		i;
	void	**tmp;

	if (tab == NULL)
		return ;
	while (--dimension)
	{
		i = 0;
		tmp = &tab;
		while (tmp[i])
		{
			free(tmp[i]);
			i++;
		}
	}
	free(tab);
}
