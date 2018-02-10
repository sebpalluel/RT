/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/18 18:21:40 by psebasti          #+#    #+#             */
/*   Updated: 2017/10/20 12:19:42 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_perror(char *name, char *error, int exit_f)
{
	ft_putstr_fd(name, 2);
	perror(error);
	if (exit_f)
		exit(EXIT_FAILURE);
}
