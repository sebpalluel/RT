/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:59:10 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/20 11:42:09 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_bool			ft_getvectfromenv(t_vec3 *vect, char *value)
{
	char		**vec_tmp;

	vec_tmp = ft_strsplit(value, ',');
	if (!vec_tmp || !vec_tmp[0] || !vec_tmp[1] || !vec_tmp[2] || vec_tmp[3])
		return (ERROR);
	vect->x = ft_atof(vec_tmp[0]);
	vect->y = ft_atof(vec_tmp[1]);
	vect->z = ft_atof(vec_tmp[2]);
	ft_tabfree((void **)vec_tmp);
	return (OK);
}

t_bool			ft_getcolfromenv(t_col *col, char *value)
{
	char		**col_tmp;

	col_tmp = ft_strsplit(value, ',');
	if (!col_tmp || !col_tmp[0] || !col_tmp[1] || !col_tmp[2] || !col_tmp[3] \
			|| col_tmp[4])
		return (ERROR);
	col->r = ft_atof(col_tmp[0]);
	col->g = ft_atof(col_tmp[1]);
	col->b = ft_atof(col_tmp[2]);
	col->s = ft_atof(col_tmp[3]);
	ft_tabfree((void **)col_tmp);
	return (OK);
}

t_bool			ft_getdoublefromenv(double *val, char *value)
{
	*val = ft_atof(value);
	return (OK);
}

t_bool			ft_getsize_tfromenv(size_t *val, char *value)
{
	*val = (size_t)ft_atoi(value);
	return (OK);
}

t_bool			ft_checkifallset(t_bool *flag, size_t numvar)
{
	while(numvar--)
		if (flag[numvar] != OK)
		{
			free(flag);
			return (ERROR);
		}
	free(flag);
	return (OK);
}

void			ft_put_pixel(t_setup *setup, int x, int y, int color)
{
	int			*tmp;
	size_t		index;
	//static t_bool one = OK;

	if (y >= (int)SCN.height || x >= (int)SCN.width || x < 0 || y < 0)
		return ;
	index = (y * SCN.width) * (SCN.img->bbp >> 3) \
			+ x * (SCN.img->bbp >> 3);
	tmp = (int *)&SCN.img->image_addr[index];
	*tmp = color;
}

