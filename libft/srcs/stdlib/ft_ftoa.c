/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 19:30:59 by psebasti          #+#    #+#             */
/*   Updated: 2017/08/02 16:18:15 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ftoa(float f)
{
	int			int_num;
	float		float_num;
	char		*int_tmp;
	char		*float_tmp;
	char		*result;

	int_num = (int)f;
	float_num = f - (float)int_num;
	while (float_num != (int)float_num)
		float_num *= 10;
	float_tmp = ft_itoa(int_num);
	int_tmp = ft_strjoin(float_tmp, ".");
	free(float_tmp);
	float_tmp = ft_itoa((int)float_num);
	if (*float_tmp == '-')
		result = ft_strjoin(int_tmp, float_tmp + 1);
	else
		result = ft_strjoin(int_tmp, float_tmp);
	free(float_tmp);
	free(int_tmp);
	return (result);
}
