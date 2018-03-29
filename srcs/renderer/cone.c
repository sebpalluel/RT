/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 20:19:17 by psebasti          #+#    #+#             */
/*   Updated: 2018/03/29 17:52:50 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*void	ft_cone_struct_pop(t_list *form, t_list *env, t_bool *flag)*/
/*{*/
	/*if (ft_strcmp(ENVSTRUCT(env)->name, "origin") == 0)*/
		/*flag[0] = ft_getvectfromenv(&CONE(form).org, ENVSTRUCT(env)->value);*/
	/*if (ft_strcmp(ENVSTRUCT(env)->name, "direction") == 0)*/
		/*flag[1] = ft_getvectfromenv(&CONE(form).dir, ENVSTRUCT(env)->value);*/
	/*if (ft_strcmp(ENVSTRUCT(env)->name, "degres") == 0)*/
		/*flag[2] = ft_getdoublefromenv(&CONE(form).theta, ENVSTRUCT(env)->value);*/
	/*flag = ft_mat_struct_pop(form, env, flag, 3);*/
	/*FORM(form)->num_arg++;*/
/*}*/

/*size_t	ft_cone(t_list **list)*/
/*{*/
	/*t_list		*env;*/
	/*t_list		*form;*/
	/*t_bool		*flag;*/

	/*env = *list;*/
	/*if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCONE + NVARMAT_MAX)))*/
		/*return (ERROR);*/
	/*ft_memset(flag, ERROR, sizeof(t_bool) * NVARCONE + NVARMAT_MAX);*/
	/*ft_lstaddend(&SCN.forms, ft_newshape());*/
	/*form = SCN.forms;*/
	/*while (form->next)*/
		/*form = form->next;*/
	/*FORM(form)->type = CON;*/
	/*while (FORM(form)->num_arg < ft_getnumvar(NVARCONE, form) \*/
			/*&& env && (env = env->next))*/
		/*ft_cone_struct_pop(form, env, flag);*/
	/*if (ft_checkifallset(flag, ft_getnumvar(NVARCONE, form)) != OK)*/
		/*return (CONE_ERROR);*/
	/*CONE(form).dir = ft_vec3normalize_r(CONE(form).dir);*/
	/**list = env;*/
	/*return (OK);*/
/*}*/

double	hit_cone(t_ray ray, t_shape *form)
{
	double a;
	double b;
	double k;
	double delta;
	t_vec3 oc;

	k = tan(form->cone.theta / 2);
	k = k * k;
	oc = ft_vec3vop_r(ray.org, form->cone.org, '-');
	a = ft_vec3dot(ray.dir, ray.dir)
		- (1 + k) * ft_vec3dot(ray.dir, form->cone.dir) *
		ft_vec3dot(ray.dir, form->cone.dir);
	b = 2 * (ft_vec3dot(ray.dir, oc) - (1 + k) *
			ft_vec3dot(ray.dir, form->cone.dir) *
			ft_vec3dot(oc, form->cone.dir));
	k = ft_vec3dot(oc, oc) - (1 + k) *
		ft_vec3dot(oc, form->cone.dir) *
		ft_vec3dot(oc, form->cone.dir);
	delta = b * b - 4 * a * k;
	if (delta <= 0.0)
		return (-1.0);
	if ((k = (-b - sqrt(delta)) / (2.0 * a)) > 0)
		return (k);
	else
		return ((-b + sqrt(delta)) / (2.0 * a));
}

t_vec3	normal_cone(t_ray ray, t_list *cone)
{
	double height;
	t_vec3 hit;
	t_vec3 oc;
	double k;
	t_vec3 norm;

	hit = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
	oc = ft_vec3vop_r(hit, CONE(cone).org, '-');
	if (ft_vec3dot(CONE(cone).dir, oc) < 0)
	{
		k = 1 / cos(CONE(cone).theta / 2.0);
		height = ft_vec3norm(ft_vec3sop_r(oc, k, '*'));
		norm = ft_vec3normalize_r(ft_vec3vop_r(oc, \
					ft_vec3sop_r(CONE(cone).dir, -height, '*'), '-'));
	}
	else
	{
		k = 1 / cos(CONE(cone).theta / 2.0);
		height = ft_vec3norm(ft_vec3sop_r(oc, k, '*'));
		norm = ft_vec3normalize_r(ft_vec3vop_r(oc, \
					ft_vec3sop_r(CONE(cone).dir, height, '*'), '-'));
	}
	return (norm);
}

t_col	intersec_cone(t_ray ray, t_list *con, t_scene *scene)
{
	t_vec3		norm;

	if (ray.dist >= 0.0)
	{
		norm = normal_cone(ray, con);
		return (diffuse(norm, con, ray, FORM(con)->mat));
	}
	return (scene->background);
}
