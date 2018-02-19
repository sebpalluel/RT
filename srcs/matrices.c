/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matop.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 00:19:29 by esuits            #+#    #+#             */
/*   Updated: 2018/02/01 17:12:22 by esuits           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "matrice.h"

int		init_mat(t_mat *mat, int i, int j)
{
	int		a;

	mat->i = i;
	mat->j = j;
	if (!(mat->mat = malloc(sizeof(double*) * i)))
		return (0);
	a = -1;
	while (++a < i)
		if (!(mat->mat[a] = ft_memalloc(sizeof(double) * j)))
			return (0);
	return (1);
}

void	add_mat(t_mat *a, t_mat *b)
{
	int		x;
	int		y;

	if (a->i != b->i || a->j != b->j)
		return ;
	x = -1;
	while (++x < a->i && (y = -1))
		while (++y < a->j)
			a->mat[x][y] += b->mat[x][y];
}

t_mat	*mult_mat(t_mat a, t_mat b)
{
	int		x;
	int		y;
	int		k;
	t_mat	*res;

	res = NULL;
	if (a.j != b.i)
		return (NULL);
	if (!(init_mat(res, a.i, b.j)))
		return (NULL);
	x = -1;
	while (++x < a.i && (y = -1))
		while (++y < b.j && (k = -1))
			while (++k < a.j)
				res->mat[x][y] += a.mat[x][k] * b.mat[k][y];
	return (res);
}

void	scale_mat(double a, t_mat *res)
{
	int		x;
	int		y;

	x = -1;
	while (++x < res->i && (y = -1))
		while (++y < res->j)
			res->mat[x][y] *= a;
}

t_vect	vect_dot(t_vect u, t_vect v)
{
	t_vect w;

	w.x = u.x * v.x;
	w.y = u.y * v.y;
	w.z = u.z * v.z;
	return (w);
}
