/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esuits <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/03 16:29:07 by esuits            #+#    #+#             */
/*   Updated: 2018/02/21 14:00:24 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

//double	hit_cyl(t_ray ray, t_formes *forme)
//{
//	double a;
//	double b;
//	double c;
//	double delta;
//	t_vec3 tmp;
//
//	tmp = vect_mult(forme->cyl.dir, ray.dir);
//	a = vect_mult_scale(tmp, tmp);
//	b = 2.0 * vect_mult_scale(tmp, vect_mult(forme->cyl.dir, vect_sub(ray.org,
//					forme->cyl.pos)));
//	tmp = vect_mult(forme->cyl.dir, vect_sub(ray.org, forme->cyl.pos));
//	c = vect_mult_scale(tmp, tmp) - forme->cyl.r * forme->cyl.r;
///*	oc = vect_sub(ray.org, forme->cyl.pos);
//	a = vect_mult_scale(ray.dir, ray.dir) - (vect_mult_scale(ray.dir, forme->cyl.dir)
//			* vect_mult_scale(ray.dir, forme->cyl.dir));
//	b = 2.0 * (vect_mult_scale(ray.dir, oc) - (vect_mult_scale(ray.dir,
//					forme->cyl.dir)
//			* vect_mult_scale(oc, forme->cyl.dir)));
//	c = vect_mult_scale(oc, oc) - vect_mult_scale(vect_scale(forme->cyl.r, oc)
//			, vect_scale(forme->cyl.r, oc)) - forme->cyl.r * forme->cyl.r;*/
//	delta = b * b - 4.0 * a * c;
//	if (delta <= 0.0)
//		return (-1.0);
//	return ((-b - sqrt(delta)) / (2.0 * a));
//}
//
//t_vec3	normal_cyl(t_ray ray, t_cyl cyl)
//{
//	t_vec3 hit;
//	t_vec3 oc;
//	double height;
//	t_vec3 norm;
//
//	hit = vect_add(ray.org, vect_scale(ray.dist, ray.dir));
//	oc = vect_sub(hit, cyl.pos);
//	height = vect_mult_scale(cyl.dir, oc);
//	norm = normal_vect(vect_sub(oc, vect_scale(height, cyl.dir)));
//	return (norm);
//}
//
//t_col	intersec_cyl(t_ray ray, t_formes *obj, t_env env)
//{
//	if (ray.dist >= 0.0)
//	{
//		obj->norm = normal_cyl(ray, obj->cyl);
////		return (init_col(1,1,1,1));
//	//	return (mult_scale_col(1 - vect_mult_scale(obj->norm, ray.dir), init_col(1,1,1,1)));
//		return (diffuse(env, obj, ray, obj->cyl.col));
//	}
//	return (BACK_COLOR);
//}

void			ft_cylindre_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&CONE(form).org, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "direction") == 0)
		flag[1] = ft_getvectfromenv(&CONE(form).dir, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "degres") == 0)
		flag[2] = ft_getdoublefromenv(&CONE(form).theta, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[3] = ft_getcolfromenv(&CONE(form).mat.col, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "diffuse") == 0)
		flag[4] = ft_getdoublefromenv(&CONE(form).mat.diffuse, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "specular") == 0)
		flag[5] = ft_getdoublefromenv(&CONE(form).mat.specular, \
				ENVSTRUCT(env)->value);
	FORM(form)->num_arg++;
}


size_t			ft_cylindre(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*form;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCYLINDRE)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCYLINDRE);
	ft_lstaddend(&SCN.forms, ft_newform());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = CYL;
	while (FORM(form)->num_arg < NVARCYLINDRE && env && (env = env->next))
		ft_cylindre_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, NVARCYLINDRE) != OK)
		return (setup->error = CYLINDRE_ERROR);
	CONE(form).dir = normal_vect(CONE(form).dir);
	*list = env;
	return (OK);
}
