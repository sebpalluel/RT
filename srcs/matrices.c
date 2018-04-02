/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                            :+:      :+:    :+:*/
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 00:19:29 by esuits            #+#    #+#             */
/*   Updated: 2018/02/27 14:48:49 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		init_mat(t_matrix *mat, int i, int j)
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

void	add_mat(t_matrix *a, t_matrix *b)
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

t_matrix	*mult_mat(t_matrix a, t_matrix b)
{
	int		x;
	int		y;
	int		k;
	t_matrix	*res;

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

void	scale_mat(double a, t_matrix *res)
{
	int		x;
	int		y;

	x = -1;
	while (++x < res->i && (y = -1))
		while (++y < res->j)
			res->mat[x][y] *= a;
}

double	det_mat(t_vec3 a, t_vec3 b, t_vec3 c)
{
	return (a.x * b.y * c.z + b.x * c.y * a.z + c.x * a.y * b.z - c.x * b.y * a.z - a.x * c.y * b.z - b.x * a.y * c.z);
}
