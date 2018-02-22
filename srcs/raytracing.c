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

// ft_trace(ray.orig, ray.dir, ray.size, setup /* stock les obj */, ray.hit)
t_bool ft_trace(t_ray *ray,t_setup *setup, t_forms *form)
{
	size_t		i; // correspond au type d'objet (par example SPH = 0 et PLN = 1), on tombera donc dans les fonctions d'intersections correspondantes
	double		dist;
	t_bool		hit_once;
	double		t_near;
	double		t;
	t_list		*list;

	i = 0;
	t = MAX_INT;
	t_near = MAX_INT;
	hit_once = FALSE;
	dist = 0;
	list = SCN.forms;
	while (list) // ce qui permet de savoir quel est l'objet rencontre et sa fonction d'intersection
	{
		ray->hit = FALSE; // je part du principe que ca n'a pas hit
		if (FORM(list)->type <= 3)
		{
			ray->hit = param()[FORM(list)->type](ray, FORM(list), &t);
			if (ray->hit == TRUE && t < t_near)
			{
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
   typedef struct		s_ray
   {
   double			size; // dist entre le point d'origine et l'objet touche le plus proche
   t_bool			hit; //Nathan remplacer par l index de l objet pointé
   size_t			obj; // de quel type de forme il s'agit
   size_t			objn; // l'index de l'objet (par exemple sphere[objn])
   t_vec3			orig; // pos de la camera
   t_vec3			dir;
   }					t_ray;
   */
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
 **      Nhit = Phit - center; () (calcul de la normale au point d'intersection)
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
 */

double max(double a, double b) {
	return (a >= b ? a : b);
}

/* COMMENT 1
**	t_vec2 hit_text; // pas besoin pour l'instant?
**	ft_get_surface_data(&hit_point, &hit_nrml, &hit_text); set hit_nrml et hit_text, pour shader le point, permet meilleur calcul de la couleur
**	// Use the normal and texture coordinates to shade the hit point.
**	// The normal is used to compute a simple facing ratio and the texture coordinate
**	// to compute a basic checker board pattern
**	float scale = 4;
**	float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5);
**	hitColor = std::max(0.f, Nhit.dotProduct(-dir)) * mix(hitObject->color, hitObject->color * 0.8, pattern);
*/
t_col ft_cast_ray(int i, int j, t_ray ray, t_setup *setup)
{
	// double shade;
	t_col hit_col;
	t_forms form;

	hit_col = setup->background;
	i = 0;
	j = 0;
	if (ft_trace(&ray, setup, &form))
	{
		/*
		**	ici j ai ma forme rencontrée dans form
		**	ma distance dans ray.dist
		** Fonction get surface data (la normale au point d intersection, le hit point, la texture)
		** je lance un shadow ray (car pour l instant toute nos surface sont diffuse)
		** ft_trace(shadow_ray, setup, &form) voir si ok que je balance form la, pas forcement top
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
	return (hit_col);
}

/*
   TODO Notes sur ft_cast_ray

// retourne couleur de l'objet
on doit :
 ** trouver l'objet
 ** set la hit_col a la couleur de l'objet rencontré
*/

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
// MAYA
// float x = (2 * (pix.y + 0.5) / (float)SCN.width - 1) * scale;
// float y = (1 - 2 * (pix.x + 0.5) / (float)SCN.height) * scale * 1 / imageAspectRatio;
// TODO Refacto
void			*ft_raytracing(void *a) // Nathan: en fait ici c est la fonction de render
{
	t_setup		*setup;
	t_pix		pix;
	t_ray		ray;
	t_vec3 orig = {0.0, 0.0, 0.0};
	t_col	col = {1., 0., 0., 0.};
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
			float scale = tan(DEG2RAD((FOV * 0.5)));
			float imageAspectRatio = SCN.width / (float)SCN.height;
			float x = (2 * (pix.x + 0.5) / (float)SCN.width - 1) * imageAspectRatio * scale;
			float y = (1 - 2 * (pix.y + 0.5) / (float)SCN.height) * scale;
			t_vec3 dir = {x, y, -1};
			multDirMatrix(&dir, &ray.dir, setup->camToWorld);
			ft_vec3normalize(&ray.dir);
			col = ft_cast_ray(pix.x, pix.y, ray, setup);
			// ft_put_pixel(setup, pix.x, pix.y, ft_coltohex(&col));
			ft_put_pixel(setup, pix.x, pix.y, coltoi(col)); //TODO adapt here for scene
		}
	}
	pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
