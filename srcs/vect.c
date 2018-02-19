/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 04:50:31 by esuits            #+#    #+#             */
/*   Updated: 2018/02/19 16:46:10 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect	init_vect(double x, double y, double z)
{
	t_vect v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

void	vect_mat_mult(t_mat a, t_vect *u)
{
	double tmpx;
	double tmpy;

	if (a.i != 3 || a.j != 3)
		return ;
	tmpx = u->x * a.mat[0][0] + u->y * a.mat[0][1] + u->z * a.mat[0][2];
	tmpy = u->x * a.mat[1][0] + u->y * a.mat[1][1] + u->z * a.mat[1][2];
	u->z = u->x * a.mat[2][0] + u->y * a.mat[2][1] + u->z * a.mat[2][2];
	u->x = tmpx;
	u->y = tmpy;
}

t_vect	vect_scale(double a, t_vect v)
{
	v.x *= a;
	v.y *= a;
	v.z *= a;
	return (v);
}

t_vect	vect_mult(t_vect u, t_vect v)
{
	double tmpx;
	double tmpy;

	tmpx = u.y * v.z - u.z * v.y;
	tmpy = u.z * v.x - u.x * v.z;
	u.z = u.x * v.y - u.y * v.x;
	u.x = tmpx;
	u.y = tmpy;
	return (u);
}

t_vect	vect_add(t_vect u, t_vect v)
{
	u.x += v.x;
	u.y += v.y;
	u.z += v.z;
	return (u);
}
