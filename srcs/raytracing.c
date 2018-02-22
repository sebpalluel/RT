/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/19 20:12:01 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <math.h>


double max(double a, double b) {
	return (a >= b ? a : b);
}

/*
**	test les intersections rayon | forme
**	au retour de la fonction on a:
**		la forme la plus proche rencontrée dans form
**		la distance a cette cette forme dans ray.dist
*/
t_bool ft_trace(t_ray *ray,t_setup *setup, t_forms *form)
{
	double		dist;
	t_bool		hit_once;
	double		t_near;
	double		t;
	t_list		*list;

	t = MAX_INT;
	t_near = MAX_INT;
	hit_once = FALSE;
	dist = 0;
	list = SCN.forms;
	while (list) /* itere sur tous les objets de la scene */
	{
		ray->hit = FALSE;
		if (FORM(list)->type <= 3)
		{
			ray->hit = param()[FORM(list)->type](ray, FORM(list), &t); /* test la routine d intersection correspondant a l objet */
			if (ray->hit == TRUE && t < t_near && t < ray->dist)
			{
				// ICI CHECK SI L OBJET RENCONTRE DANS LE SHADOW RAY EST AVANT LA SOURCE DE LUMIERE (t < ray->dist)
				// SAUF QUE CA MARCHE PAS IL TRAVERSE LA LUMIERE
				hit_once = ray->hit;
				t_near = t;
				ray->dist = t;
				*form = *FORM(list);
			}
		}
		list = list->next;
	}
	return (hit_once);
}

/*
   void ft_get_surface_data(t_vec3 *hit_point, t_vec3 *hit_nrml, t_vec3 *hit_text)
   {
 *
 **	void getSurfaceData(const Vec3f &Phit, Vec3f &Nhit, Vec2f &tex) const
 **  {
 ** 			Set surface data such as normal and texture coordinates at a given point on the surface
 ** 			\param Phit is the point ont the surface we want to get data on
 ** 			\param[out] Nhit is the normal at Phit
 ** 			\param[out] tex are the texture coordinates at Phit
 **************
 **      Nhit = Phit - center; () (calcul de la normale au point d'intersection) pour la sphere
 **      Nhit.normalize();  On normalise le vecteur
 **************
 **      In this particular case, the normal is simular to a point on a unit sphere
 **      centred around the origin. We can thus use the normal coordinates to compute
 **      the spherical coordinates of Phit.
 **      atan2 returns a value in the range [-pi, pi] and we need to remap it to range [0, 1]
 **      acosf returns a value in the range [0, pi] and we also need to remap it to the range [0, 1]
 **************
 **      tex.x = (1 + atan2(Nhit.z, Nhit.x) / M_PI) * 0.5; -> a defini je suis pas mega au clair
 **      tex.y = acosf(Nhit.y) / M_PI;
 **  }
 *
 }

   TODO Notes sur ft_cast_ray

// retourne couleur de l'objet
on doit :
 ** trouver l'objet
 ** set la hit_col a la couleur de l'objet rencontré
*/

t_col ft_cast_ray(int i, int j, t_ray ray, t_setup *setup)
{
	// double shade;
	t_col hit_col;
	t_forms form;
	/* en dur en attendant */
	t_lgt light;
	t_col lgt_col = {1,1,1,1};
	t_vec3 vect = {1.0, 0.0, -3.};
	light.type = 0;
	light.vect = vect;
	light.col = lgt_col;
	/* FIN en dur en attendant */
	hit_col = setup->background;
	i = 0;
	j = 0;

	if (ft_trace(&ray, setup, &form))
	{
		if (form.type == SPH)
		{
			hit_col = form.sph.mat.col;
		}
		else if (form.type == PLN)
		{
			hit_col = form.plan.mat.col;
		}
		else if (form.type == CON)
		{
			hit_col = form.cone.mat.col;
		}
		else if (form.type == CYL)
		{
			hit_col = form.cldre.mat.col;
		}
		else
		{
			hit_col.r = 1.;
			hit_col.g = 0.;
			hit_col.b = 0.;
			hit_col.s = 1.;
		}

		t_vec3 hit_point = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
		// lightDir = pos - P;
		t_vec3 light_dir = ft_vec3vop_r(light.vect, hit_point, '-');
		//     // compute the square distance
		//     float r2 = lightDir.norm();
		//     dist = sqrtf(r2);
		double r2 = ft_dotproduct(light_dir,light_dir); // TODO IMPORTANT VERIFIER CE TRUC
		double dist = sqrt(r2);
		t_ray  sdw_ray;
		sdw_ray.org = hit_point;
		sdw_ray.dir = light_dir;
		sdw_ray.dist = dist;
			// t_vec3 hit_nrml = ft_vec3vop_r(hit_point, form.sph.ctr, '-');
			// double bias = 0.0001;
			// sdw_ray.org = ft_vec3vop_r(sdw_ray.org, ft_vec3sop_r(hit_nrml, bias, '*'), '+');
		// if (form.type == PLN) {
			t_bool vis;
			vis = !ft_trace(&sdw_ray, setup, &form);
			hit_col = mult_scale_col(vis, hit_col);
		// }
		/*
		**	ici j ai ma forme rencontrée dans form
		**	ma distance dans ray.dist
		** Fonction get surface data (la normale au point d intersection, le hit point, la texture)
		**	normale au point d interection -> besoin de type d'obj, ray, form => singleton ?
		**	hit_point -> besoin ray.org et ray.dist
		** je lance un shadow ray (car pour l instant toute nos surface sont diffuse)
		** ft_trace(shadow_ray, setup, &form) voir si ok que je balance form la, pas forcement top
		**	shadow ray -> ray.origine = hit_point
		**	shadow ray -> ray.dir = direction de la lumiere
		** SI True : color = background
		** SINON
		** 	get_color()
		**		a partir des surfaces data je calcul ma couleur,
		**		besoin du rayon, de la couleur de l obj (ds surface data)
		**
		*/
		// t_vec3 hit_point = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
		// t_vec3 hit_nrml = ft_vec3vop_r(hit_point, OBJDEF.sphere[ray.objn].pos, '-'); // pas besoin pour l instant ?
		// ft_vec3normalize(&hit_nrml); //add COMMENT 1 under
	}
	return (hit_col);
}

void multDirMatrix(t_vec3 *src, t_vec3 *dst, double **x) {
	double a;
	double b;
	double c;

	a = src->x * x[0][0] + src->y * x[1][0] + src->z * x[2][0];
	b = src->x * x[0][1] + src->y * x[1][1] + src->z * x[2][1];
	c = src->x * x[0][2] + src->y * x[1][2] + src->z * x[2][2];

	dst->x = a;
	dst->y = b;
	dst->z = c;
}

void multVecMatrix(t_vec3 *src, t_vec3 *dst, double **x) {
	double a;
	double b;
	double c;
	double w;

	a = src->x * x[0][0] + src->y * x[1][0] + src->z * x[2][0] + x[3][0];
	b = src->x * x[0][1] + src->y * x[1][1] + src->z * x[2][1] + x[3][1];
	c = src->x * x[0][2] + src->y * x[1][2] + src->z * x[2][2] + x[3][2];
	w = src->x * x[0][3] + src->y * x[1][3] + src->z * x[2][3] + x[3][3];

	dst->x = a / w;
	dst->y = b / w;
	dst->z = c / w;
}

// TODO CameraToWorld transfo https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
// TODO Refacto
void			*ft_raytracing(void *a) // Nathan: en fait ici c est la fonction de render
{
	/* on a trop de variable ici*/
	/* isoler thread ? */
	t_setup		*setup;
	t_pix		pix;
	t_ray		ray;
	/* ici on doit init avec la position de la camera */
	t_vec3 orig = {0.0, 0.0, 0.0};
	t_col	col;
	pthread_t	id;
	int			i;
	size_t		inc;

	setup = (t_setup *)a;
	multVecMatrix(&orig, &ray.org, setup->camToWorld); // ft_setup_cam(setup); // fonction qui permet d'initialiser la camera suivant les donnee du parser
	// ft_vec3normalize(&ray.org); TODO voir si besoin
	id = pthread_self();
	i = -1;
	inc = SCN.height / THREAD;
	while (++i < THREAD) // permet d'identifier dans quel thread on est
		if (pthread_equal(id, setup->thrd[i]))
			break ;
	pix.y = inc * i - 1;
	pthread_mutex_lock(&setup->mutex.mutex);
	while (++pix.y <= (int)(inc * (i + 1) - 1))
	{
		pix.x = -1;
		while (++pix.x < (int)SCN.width)
		{
			/* REFACTO dans sa propre fonction */
			float scale = tan(DEG2RAD((FOV * 0.5)));
			float imageAspectRatio = SCN.width / (float)SCN.height;
			float x = (2 * (pix.x + 0.5) / (float)SCN.width - 1) * imageAspectRatio * scale;
			float y = (1 - 2 * (pix.y + 0.5) / (float)SCN.height) * scale;
			t_vec3 dir = {x, y, -1};
			/* fin REFACTO */
			multDirMatrix(&dir, &ray.dir, setup->camToWorld);
			ft_vec3normalize(&ray.dir);
			ray.dist = MAX_INT;
			col = ft_cast_ray(pix.x, pix.y, ray, setup);
			ft_put_pixel(setup, pix.x, pix.y, coltoi(col)); //TODO adapt here for scene
		}
	}
	pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
