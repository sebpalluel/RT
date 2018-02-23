/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 04:50:31 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 17:20:17 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vec3		init_vec3(double x, double y, double z)
{
	t_vec3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

void		vect_mat_mult(t_matrix a, t_vec3 *u)
{
	double	tmpx;
	double	tmpy;

	if (a.i != 3 || a.j != 3)
		return ;
	tmpx = u->x * a.mat[0][0] + u->y * a.mat[0][1] + u->z * a.mat[0][2];
	tmpy = u->x * a.mat[1][0] + u->y * a.mat[1][1] + u->z * a.mat[1][2];
	u->z = u->x * a.mat[2][0] + u->y * a.mat[2][1] + u->z * a.mat[2][2];
	u->x = tmpx;
	u->y = tmpy;
}

t_vec3		vect_scale(double a, t_vec3 v)
{
	v.x *= a;
	v.y *= a;
	v.z *= a;
	return (v);
}

t_vec3		vect_mult(t_vec3 u, t_vec3 v)
{
	double	tmpx;
	double	tmpy;

	tmpx = u.y * v.z - u.z * v.y;
	tmpy = u.z * v.x - u.x * v.z;
	u.z = u.x * v.y - u.y * v.x;
	u.x = tmpx;
	u.y = tmpy;
	return (u);
}

t_vec3		vect_add(t_vec3 u, t_vec3 v)
{
	u.x += v.x;
	u.y += v.y;
	u.z += v.z;
	return (u);
}
