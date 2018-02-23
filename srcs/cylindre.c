/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:40:58 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/20 11:34:57 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			ft_cldre_struct_pop(t_list *form, t_list *env, t_bool *flag)
{
	if (ft_strcmp(ENVSTRUCT(env)->name, "origin") == 0)
		flag[0] = ft_getvectfromenv(&CLDRE(form).pos, ENVSTRUCT(env)->value);
  if (ft_strcmp(ENVSTRUCT(env)->name, "direction") == 0)
		flag[1] = ft_getvectfromenv(&CLDRE(form).dir, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "radius") == 0)
		flag[2] = ft_getdoublefromenv(&CLDRE(form).r, ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "color") == 0)
		flag[3] = ft_getcolfromenv(&CLDRE(form).mat.col, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "diffuse") == 0)
		flag[4] = ft_getdoublefromenv(&CLDRE(form).mat.diffuse, \
				ENVSTRUCT(env)->value);
	if (ft_strcmp(ENVSTRUCT(env)->name, "specular") == 0)
		flag[5] = ft_getdoublefromenv(&CLDRE(form).mat.specular, \
				ENVSTRUCT(env)->value);
	FORM(form)->num_arg++;
}


size_t			ft_cldre(t_list **list)
{
	t_setup		*setup;
	t_list		*env;
	t_list		*form;
	t_bool		*flag;

	setup = get_st();
	env = *list;
	if (!(flag = (t_bool *)malloc(sizeof(t_bool) * NVARCLDRE)))
		return (ERROR);
	ft_memset(flag, ERROR, sizeof(t_bool) * NVARCLDRE);
	ft_lstaddend(&SCN.forms, ft_newform());
	form = SCN.forms;
	while (form->next)
		form = form->next;
	FORM(form)->type = CYL;
	while (FORM(form)->num_arg < NVARCLDRE && env && (env = env->next))
		ft_cldre_struct_pop(form, env, flag);
	if (ft_checkifallset(flag, NVARCLDRE) != OK)
		return (setup->error = CONE_ERROR); // TODO ERROR POUR CYLINDRE
	*list = env;
	return (OK);
}

t_bool ft_cldre_intersect(t_ray *ray, t_forms *form, double *t)
{
	float t0;
	float t1;
	double DV;
	double distV;
	double abc[3];
	t_vec3 dist;

	dist = ft_vec3vop_r(ray->org, form->cldre.pos, '-');
	DV = ft_dotproduct(ray->dir, form->cldre.dir);
	distV = ft_dotproduct(dist, form->cldre.dir);
	abc[0] = ft_dotproduct(ray->dir, ray->dir) - (DV * DV);
	abc[1] = 2 * (ft_dotproduct(ray->dir, dist) - DV * distV);
	abc[2] = ft_dotproduct(dist, dist) - (distV * distV) - (form->cldre.r * form->cldre.r);
	if (!solve_quadratic(abc, &t0, &t1)) // TODO DUPLICATE WITH sphere.c sphere_param
		return FALSE;
	if (t0 > t1)
		ft_swap(&t0, &t1, sizeof(float));
	if (t0 < 0) {
		t0 = t1;
		if (t0 < 0)
			return FALSE;
	}
	*t = t0;
	return (TRUE);
}