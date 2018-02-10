/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabnullfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 18:14:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/01/11 18:20:03 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabnullfree(void ***tab)
{
	int	i;

	i = 0;
	if (*tab == NULL)
		return ;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		(*tab)[i++] = NULL;
	}
	free(*tab);
	*tab = NULL;
}
