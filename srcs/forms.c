/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:57:54 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/28 11:29:56 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_list			*ft_newform(void)
{
	t_list		*form;

	if (!(form = (t_list*)malloc(sizeof(t_list))) || \
			!(form->content = (t_forms*)ft_memalloc(sizeof(t_forms))))
		return (NULL);
	form->content_size = sizeof(t_forms);
	form->next = NULL;
	return (form);
}

void			illuminate(t_hit *hit, t_mat mat, t_lgt *light)
{
	float		r2;
	t_vec3		lightdir;
	double		dist;
	double		lambert;

	lightdir = ft_vec3vop_r(light->vect, hit->pos, '-');
	r2 = ft_dotproduct(lightdir, lightdir);
	ft_vec3normalize(&lightdir);
	dist = sqrt(r2);
	lambert = ft_max(0, ft_dotproduct(hit->nrml, lightdir));
	hit->col = mult_scale_col_limited(lambert, \
			mult_scale_col_limited(mat.diffuse, mat.col));
}

void			init_sdw_ray(t_ray *sdw_ray, t_lgt *light, t_hit *hit)
{
	double bias;
	t_vec3 lightdir;
	t_vec3 tmp;

	bias = 0.0001;
	lightdir = ft_vec3vop_r(light->vect, hit->pos, '-');
	sdw_ray->org = ft_vec3vop_r(hit->pos, \
			ft_vec3sop_r(hit->nrml, bias, '*'), '+');
	sdw_ray->dir = ft_vec3normalize_r(lightdir);
	tmp = ft_vec3vop_r(hit->pos, light->vect, '-');
	sdw_ray->dist = sqrt(ft_dotproduct(tmp, tmp));
}
