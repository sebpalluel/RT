/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:59:10 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/10 18:12:57 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_bool			ft_getvec3fromenv(t_vec3 *vec3, char *value)
{
	char		**vec_tmp;

	vec_tmp = ft_strsplit(value, ',');
	if (!vec_tmp || !vec_tmp[0] || !vec_tmp[1] || !vec_tmp[2] || vec_tmp[3])
		return (ERROR);
	vec3->x = ft_atof(vec_tmp[0]);
	vec3->y = ft_atof(vec_tmp[1]);
	vec3->z = ft_atof(vec_tmp[2]);
	ft_tabfree((void **)vec_tmp);
	return (OK);
}

t_bool			ft_getcolfromenv(t_color *col, char *value)
{
	char		**col_tmp;

	col_tmp = ft_strsplit(value, ',');
	if (!col_tmp || !col_tmp[0] || !col_tmp[1] || !col_tmp[2] || col_tmp[3])
		return (ERROR);
	col->r = ft_atoi(col_tmp[0]);
	col->g = ft_atoi(col_tmp[1]);
	col->b = ft_atoi(col_tmp[2]);
	ft_tabfree((void **)col_tmp);
	return (OK);
}

t_bool			ft_getfloatfromenv(float *val, char *value)
{
	*val = ft_atof(value);
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

	if (y >= (int)setup->height || x >= (int)setup->width || x < 0 || y < 0)
		return ;
	index = (y * setup->width) * (IMG->bbp >> 3) \
			+ x * (IMG->bbp >> 3);
	tmp = (int *)&IMG->image_addr[index];
	*tmp = color;
}

