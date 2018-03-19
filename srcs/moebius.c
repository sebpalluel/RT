/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moebius.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/11 16:29:07 by esuits            #+#    #+#             */
/*   Updated: 2018/03/19 14:27:21 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

//static inline double	calc(double x, double ox, double y, double oy)
//{
//	return (x * x * oy + 2 x * y * ox);
//}
//
//static inline double	ft_2min_pos(double a, double b)
//{
//	if (a < b && a > 0)
//		return (a)
//	else
//		return (b);
//}
//
//double			hit_moebius(t_ray ray, t_shape *shape)
//{
//	double 	abcd[4];
//	t_vec3	dir;
//	t_vec3	o;
//	t_shape torus;
//	double dist;
//
//	o = ft_vec3vop_r(ray.org, form->moeb.ctr, '-')
//	d = form->moeb.dir;
//	torus.dir = d;
//	torus.ctr = shape.ctr;
//	torus.bradius = shape.radius;
//	torus.sradius = shape.height / 2.0;
//	abcd[0] = d.x * d.x * d.y + d.y * d.y * d.y - 2 * d.x * d.x * d.z - 2 * d.y * d.y * d.z + d.y * d.z * d.z;
//	abcd[1] = calc(d.x, o.x, d.y, o.y) + 3 * d.y * d.y * o.y - 2 * form->moeb.r * d.x * d.y - 2 * calc(d.x, o.x, d.z, o.z) - 2 * calc(d.y, o.y, d.z, o.z) + calc(d.z, o.z, d.y, o.y);
//	abcd[2] = -form->moeb.r * form->moeb.r * d.y + 2 * d.x * o.x * o.y + d.y * o.x * o.x + 3 * d.y * o.y * o.y - 2 * form->moeb.r * (o.x * d.y + d.x * o.y) - 2 * (2 * d.x * o.x * o.z + d.z * o.x * o.x) - 2 * (2 * d.y * o.y * o.z + d.z * o.y * o.y) + 2 * d.z * o.z * o.y + d.y * o.z * o.z;
//	abcd[3] = -form->moeb.r * form->moeb.r * o.y + o.x * o.x * o.y + o.y * o.y * o.y - 2 * form->moeb.r * o.x * o.y - 2 * o.x * o.x * o.z - 2 * o.y * o.y * o.z  + o.y * o.z * o.z;
//
//	r = ft_resolve_cubic_min(abcd[0], abcd[1], abcd[2], abcd[3]);
//	if ft_is_in_torus(r, ray);
//}
//
//t_col			intersec_moebius(t_ray ray, t_list *moebius, t_setup *setup)
//{
//	t_vec3		norm;
//
//	if (ray.dist >= 0.0)
//	{
//		norm = normal_sphere(ray, moebius);
//		return (diffuse(norm, sph, ray, FORM(moebius)->mat));
//	}
//	return (setup->background);
//}

void	ft_moebius_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "center") == 0)
		flag[0] = ft_getvectfromenv(&MOEB(form).ctr, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "axe_x") == 0)
		flag[1] = ft_getvectfromenv(&MOEB(form).axe_x, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "axe_y") == 0)
		flag[2] = ft_getvectfromenv(&MOEB(form).axe_y, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "radius") == 0)
		flag[3] = ft_getdoublefromenv(&MOEB(form).r, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "width") == 0)
		flag[4] = ft_getdoublefromenv(&MOEB(form).width, ENVSTRUCT(env)->value);
	flag = ft_mat_struct_pop(form, env, flag, 5);
	FORM(form)->num_arg++;
}

size_t	ft_moebius(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*form;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARMOEBIUS)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARMOEBIUS);
	ft_lstaddend(&SCN.forms, ft_newshape());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = CYL;
	while (FORM(form)->num_arg < NVARMOEBIUS && env && (env = env->next))
		ft_moebius_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, NVARMOEBIUS) != OK)
		return (setup->error = MOEBIUS_ERROR);
	//MOEB(form).dir = ft_vec3normalize_r(MOEB(form).dir);
	*list = env;
	return (OK);
}
