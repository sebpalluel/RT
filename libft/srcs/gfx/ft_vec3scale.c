/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:17:14 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/26 19:19:34 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec3	ft_vec3scale(t_vec3 v, double a)
{
	v.x *= a;
	v.y *= a;
	v.z *= a;
	return (v);
}
