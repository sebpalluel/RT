/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 16:05:22 by psebasti         ###   ########.fr       */
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
t_forms 		*ft_trace(t_ray *ray, t_setup *setup)
{
	double		dist;
	t_forms		*form;
	double		t_near;
	double		t;
	t_list		*list;

	t = MAX_INT;
	t_near = MAX_INT;
	form = NULL;
	dist = 0;
	list = SCN.forms;
	while (list) /* itere sur tous les objets de la scene */
	{
		ray->hit = FALSE;
		if (FORM(list)->type <= 3)
		{
			ray->hit = param()[FORM(list)->type](ray, FORM(list), &t); /* test la routine d intersection correspondant a l objet */
			if ((ray->hit == TRUE && (t < t_near || t < ray->dist)))
			{
				// ICI CHECK SI L OBJET RENCONTRE DANS LE SHADOW RAY EST AVANT LA SOURCE DE LUMIERE (t < ray->dist)
				// SAUF QUE CA MARCHE PAS IL TRAVERSE LA LUMIERE
				t_near = t;
				ray->dist = t;
				form = FORM(list);
			}
		}
		list = list->next;
	}
	return (form);
}

// static t_bool	ft_trace_shadow(t_ray *ray, t_setup *setup, t_forms *obj)
// {
// 	t_forms		*shadow;
//
// 	shadow = ft_trace(ray, setup);
// 	if (shadow && shadow != obj)
// 		return (TRUE);
// 	return (FALSE);
// }
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

t_col mult_scale_col_limited(double t, t_col col)
{
	col.r = col.r * t;
	col.g = col.g * t;
	col.b = col.b * t;
	if (col.r > 1)
		col.r = 1;
	if (col.g > 1)
		col.g = 1;
	if (col.b > 1)
		col.b = 1;
	return (col);
}

t_col illuminate(t_vec3 *p, t_vec3 *hit_nrml, t_mat *mat, t_lgt *light)
{
	float r2;
	t_vec3 lightdir;
	// t_col light_intensity;
	double dist;
	// t_color col;

	// lightdir = ft_vec3vop_r(light->vect, *p, '-');
	lightdir = ft_vec3vop_r(light->vect, *p, '-');
	r2 =  ft_dotproduct(lightdir,lightdir) ; //scratchapixel vec3.norm()x * x + y * y + z * z
	ft_vec3normalize(&lightdir);
	dist = sqrt(r2);
	// lightdir.x /= dist;
  // //
	// lightdir.y /= dist;
	// lightdir.z /= dist;
	// *lightIntensity = color * intensity / (4 * M_PI * r2);
	// light_intensity.r = 255 / (4 * M_PI * r2);
	// light_intensity.g = 255 / (4 * M_PI * r2);
	// light_intensity.b = 255 / (4 * M_PI * r2);``
	// printf("col: 255 / (4 * M_PI * r2): %f\t", 255 / (4 * M_PI * r2));
	// if (form->type != PLN)
	// {
	// 	printf("light dir: x->%f, y->%f, z->%f\n", lightdir.x, lightdir.y, lightdir.z);
	// 	printf("hit normal: x->%f, y->%f, z->%f\n", hit_nrml->x, hit_nrml->y, hit_nrml->z);
	// }
	double lambert =  max(0, ft_dotproduct(*hit_nrml, lightdir));
	// if (form->type == PLN)
	// 	printf("%f\n", lambert);
	// double lambert = light.pos - (ray.org + (ray.dist * ray.dir))
	// lambert = ft_dotproduct(*hit_nrml, lightdir);
	// lambert(t_ray ray, t_vect norm, t_lights *lights)
	// lmbrt = lambert(ray, forme->norm, env.lights);
	// https://github.com/Caradran/rtv1/blob/master/src/diffuse.c A RIEN COMPRIS
	// printf("lambert: %f\n", lambert);
	// hitObject->albedo / M_PI * light->intensity * light->color * std::max(0.f, hitNormal.dotProduct(L))
	t_col hit_col = mult_scale_col_limited(lambert ,mult_scale_col_limited(mat->diffuse/mat->specular, mat->col));
	return (hit_col);
	// ELIOT
		// addcol(interpolcol(BACK_COLOR,
		// 		mult_scale_col(env.expo / (dist * dist), multcol(col_obj,
		// 		env.lights->lgt.col)), lmbrt * lmbrt), col)
}

t_col ft_cast_ray(int i, int j, t_ray ray, t_setup *setup)
{
	// double shade;
	t_col hit_col;
	t_forms *form;
	/* en dur en attendant */
	t_lgt *light = LGT(SCN.lgts);
	/* FIN en dur en attendant */
	t_vec3 hit_nrml = {0,0,0};
	hit_col = setup->background;
	i = 0;
	j = 0;
	form = NULL;
	if ((form = ft_trace(&ray, setup)))
	{
		t_vec3 hit_point = ft_vec3vop_r(ray.org, ft_vec3sop_r(ray.dir, ray.dist, '*'), '+');
		hit_nrml = get_nrml()[form->type](ray, form);
		if (form->type == SPH)
		{
			hit_col = form->sph.mat.col;
			hit_col = illuminate(&hit_point, &hit_nrml, &form->sph.mat, light);
		}
		else if (form->type == PLN)
		{
			hit_col = form->plan.mat.col;
			hit_col = illuminate(&hit_point, &hit_nrml, &form->plan.mat, light);
			// if (hit_nrml.z < 0)
		  //    hit_nrml = ft_vec3sop_r(form->plan.nrml, -1, '*');
		}
		else if (form->type == CON)
		{
			hit_col = form->cone.mat.col;
			hit_col = illuminate(&hit_point, &hit_nrml, &form->cone.mat, light);
		}
		else if (form->type == CYL)
		{
			hit_col = form->cldre.mat.col;
			hit_col = illuminate(&hit_point, &hit_nrml, &form->cldre.mat, light);
		}
		else
		{
			hit_col.r = 1.;
			hit_col.g = 0.;
			hit_col.b = 0.;
			hit_col.s = 1.;
		}

		// lightDir = pos - P;
		t_vec3 light_dir = ft_vec3vop_r(light->vect, hit_point, '-');
		//     // compute the square distance
		//     float r2 = lightDir.norm();
		//     dist = sqrtf(r2);
		double r2 = ft_dotproduct(light_dir,light_dir); // TODO IMPORTANT VERIFIER CE TRUC
		double dist = sqrt(r2);
		t_ray  sdw_ray;
		// double lambert = ft_dotproduct(light_dir, hit_nrml) * 1;
		// hit_col = mult_scale_col(lambert , hit_col);// Une magnyfaique texture toute moche
		// float lambert = (lightRay.dir * n) * coef;
		// 		 red += lambert * current.red * currentMat.red;
		// 		 green += lambert * current.green * currentMat.green;
		// 		 blue += lambert * current.blue * currentMat.blue;
		// sdw_ray.org = hit_point;
		double bias = 0.0001;
		sdw_ray.org = ft_vec3vop_r(hit_point, ft_vec3sop_r(hit_nrml, bias,'*'), '+');
		sdw_ray.dir = light_dir;
		sdw_ray.dist = dist;
		// bool vis = !trace(hitPoint + hitNormal * options.bias, L, objects, isectShad, kShadowRay);
		// if (ft_trace(&sdw_ray, setup))
		// 	hit_col = mult_scale_col(0., hit_col);
// 		When we hit such a surface in our raytracer code, we will compute the cosine of the angle theta that the incoming ray does with the surface (via the normal) :
// float lambert = (lightRay.dir * n) * coef;
// Then we multiply that lambertian coeficient with the diffuse color property of the surface, that will give us the perceived lighting for the current viewing ray.

		//else
		//	mult_scale_col(1., hit_col);
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
			ft_put_pixel(setup, pix.x, pix.y, ft_coltoi(col)); //TODO adapt here for scene
		}
	}
	pthread_mutex_unlock(&setup->mutex.mutex);
	pthread_exit(NULL);
}
