/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3add3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 15:53:27 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/01 15:55:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_vec3		ft_vec3add3(t_vec3 a, t_vec3 b, t_vec3 c)
{
    return (ft_vec3_r(a.x + b.x + c.x, a.y + b.y + c.y, a.z + b.z + c.z));
}
