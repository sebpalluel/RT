/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_mat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 02:18:14 by esuits            #+#    #+#             */
/*   Updated: 2018/02/27 14:20:38 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_matrix	rot_mat(t_vec3 v, double theta)
{
	t_matrix rot;

	if (!(init_mat(&rot, 3, 3)))
		return (rot);
	rot.mat[0][0] = cos(theta) + v.x * v.x * (1 - cos(theta));
	rot.mat[1][1] = cos(theta) + v.y * v.y * (1 - cos(theta));
	rot.mat[2][2] = cos(theta) + v.z * v.z * (1 - cos(theta));
	rot.mat[0][1] = v.x * v.y * (1 - cos(theta)) - v.z * sin(theta);
	rot.mat[0][2] = v.x * v.z * (1 - cos(theta)) + v.y * sin(theta);
	rot.mat[1][0] = v.x * v.y * (1 - cos(theta)) + v.z * sin(theta);
	rot.mat[1][2] = v.z * v.y * (1 - cos(theta)) - v.x * sin(theta);
	rot.mat[2][0] = v.x * v.z * (1 - cos(theta)) - v.y * sin(theta);
	rot.mat[2][1] = v.z * v.y * (1 - cos(theta)) + v.x * sin(theta);
	return (rot);
}

t_matrix	id_mat(void)
{
	t_matrix id;

	if (!(init_mat(&id, 3, 3)))
		return (id);
	id.mat[0][0] = 1;
	id.mat[0][0] = 1;
	id.mat[0][0] = 1;
	return (id);
}

t_vec3		mult_vec3_mat(t_matrix a, t_vec3 b)
{
	t_vec3	res;

	res.x = b.x * a.mat[0][0] + b.y * a.mat[0][1] + b.z * a.mat[0][2];
	res.y = b.x * a.mat[1][0] + b.y * a.mat[1][1] + b.z * a.mat[1][2];
	res.z = b.x * a.mat[2][0] + b.y * a.mat[2][1] + b.z * a.mat[2][2];
	return (res);
}

t_vec3		rot_vec3(t_vec3 v, double theta, t_vec3 axis)
{
	return (mult_vec3_mat(rot_mat(axis, theta), v));
}
