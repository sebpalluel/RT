/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 10:29:07 by esuits            #+#    #+#             */
/*   Updated: 2018/03/19 15:48:26 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

//double			hit_torus(t_ray ray, t_shape *shape)
//{
//	t_vec3	o;
//	t_vec3	d;
//	double	abcde[5]
//	double	tmp[6]
//
//	o = ft_vec3vop_r(ray.org, form->moeb.ctr, '-')
//	d = form->moeb.dir;
//	tmp[0] = d.x * d.x + d.y * d.y + d.z * d.z;
//	tmp[1] = 2 * (o.x * d.x + o.y * d.y + o.z * d.z);
//	tmp[2] = o.x *o.x + o.y * o.y + o.z * o.z + 
//		(shape->torus.bradius) * (shape->torus.bradius) - 
//		(shape->torus.sradius) * (shape->torus.sradius);
//	tmp[3] = (d.x * d.x + d.y * d.y) 4 * 
//		(shape->torus.bradius) * (shape->torus.bradius);
//	tmp[4] = 8 * (shape->torus.bradius) * 
//		(shape->torus.bradius) * (o.x * d.x + o.y * d.y);
//	tmp[5] = 4 * (shape->torus.bradius) * 
//		(shape->torus.bradius) * (o.x * o.x + o.y * o.y);
//	abcde[0] = tmp[0] * tmp[0];
//	abcde[1] = 2 * tmp[1] * tmp[0] / abcde[0];
//	abcde[2] = (2 * tmp[0] * tmp[2] + tmp[1] * tmp[1] - tmp[3]) / abcde[0];
//	abcde[3] = (2 * tmp[1] * tmp[2] - tmp[4]) / abcde[0];
//	abcde[4] = (tmp[2] * tmp[2] - tmp[5]) / abcde[0];
//	return (ft_resolve_quadric_min(abcde[1], abcde[2], abcde[3], abcde[4]));
//}
//
//t_col			intersec_torus(t_ray ray, t_list *torus, t_setup *setup)
//{
//	t_vec3		norm;
//
//	if (ray.dist >= 0.0)
//	{
//		norm = normal_sphere(ray, torus);
//		return (diffuse(norm, sph, ray, FORM(torus)->mat));
//	}
//	return (setup->background);
//}

void	ft_torus_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "center") == 0)
		flag[0] = ft_getvectfromenv(&TORU(form).ctr, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "dir") == 0)
		flag[1] = ft_getvectfromenv(&TORU(form).dir, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "small_radius") == 0)
		flag[2] = ft_getdoublefromenv(&TORU(form).s_r, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "big_radius") == 0)
		flag[3] = ft_getdoublefromenv(&TORU(form).b_r, ENVSTRUCT(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 4);
	FORM(form)->num_arg++;
}

size_t	ft_torus(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*form;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARTORUS)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARTORUS);
	ft_lstaddend(&SCN.forms, ft_newshape());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = CYL;
	while (FORM(form)->num_arg < NVARTORUS && env && (env = env->next))
		ft_torus_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, NVARTORUS) != OK)
		return (setup->error = TORUS_ERROR);
	//TORU(form).dir = ft_vec3normalize_r(TORU(form).dir);
	*list = env;
	return (OK);
}
