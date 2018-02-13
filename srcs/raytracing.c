/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/10 18:48:46 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"
#include <math.h>

t_ray		ft_raycalcforpix(t_setup *setup, t_pix pix) {
	double	px;
	double	py;
	t_vec3	p;
	t_ray	ray;

	py = (-(int)SETUP.height / 2.0) + 1. * ((double)pix.y + 0.5);
	px = (-(int)SETUP.width / 2.0) + 1. * ((double)pix.x + 0.5);
	p = ft_vec3add3(CAM[CAM_N].plane_center, \
			ft_vec3sop_r(CAM[CAM_N].plane_dirX, px, '*'), \
			ft_vec3sop_r(CAM[CAM_N].plane_dirY, py, '*'));
	ray.orig = CAM[CAM_N].pos;
	ray.dir = ft_vec3unit(ft_vec3vop_r(p, CAM[CAM_N].pos, '-'));
	ray.hit = ERROR;
	return (ray);
}

//Ray ray_makeForPixel(const Camera *c, size_t x, size_t y) {
//    double dy = 1.0;
//    double dx = 1.0;
//    double py = (- c->height / 2.0) + dy * ((double)y + 0.5);
//    double px = (- c->width / 2.0) + dx * ((double)x + 0.5);
//    Vector3 p = vec3_add3(c->planeCenter,
//                          vec3_mult(c->planeDirectionX, px),
//                          vec3_mult(c->planeDirectionY, py));
//    Vector3 u_r = vec3_unit(vec3_sub(p, c->position));
//    return ray_make(c->position, u_r);
//}

int				ft_chooseobj(t_setup *setup, size_t *i)
{
	if (*i == SPH)
	{
		if (NSPHERE && SPH_N < NSPHERE)
			return (OK);
		else
			*i += 1;
	}
	if (*i == PLN)
	{
		if (NPLANE && PL_N < NPLANE)
			return (OK);
		else
			*i += 1;
	}
	return (ERROR);
}

void			ft_resetchooseobj(t_setup *setup)
{
	SPH_N = 0;
	PL_N = 0;
}

int				ft_getobjn(t_setup *setup, size_t i)
{
	if (i == SPH)
			return (SPH_N - 1);
	else if (i == PLN)
			return (PL_N - 1);
	return (0);
}

static void		ft_primray(t_setup *setup, t_ray *ray) // remplacer par trace
{
	size_t		i; // correspond au type d'objet (par example SPH = 0 et PLN = 1), on tombera donc dans les fonctions d'intersections correspondantes
	double		dist;
	t_bool		hit_once;

	i = 0;
	hit_once = ERROR; // je part du principe que ca n'a pas hit
	ray->size = MAX_INT; // j'initialise a distance infinie
	while (ft_chooseobj(setup, &i) == OK) // ce qui permet de savoir quel est l'objet rencontre et sa fonction d'intersection
	{
		// ray->hit = OBJS->param[i].paramfunc((void *)setup, *ray, &dist); // va dans la fonction d'intersection correspondante, quand i = 0, va dans ft_sphere_intersection, retourne si hit ou pas et donne la distance.
		// attention manque des infos comme la normale au point d'intersection.
		if (ray->hit == OK && dist < ray->size && ray->size > 0.0001)
		{
			ray->size = dist;
			ray->obj = i; // permet de savoir de quel type de forme il sagit
			ray->objn = ft_getobjn(setup, i); // permet de savoir l'index de la forme
			hit_once = OK;
		}
	}
	ray->hit = hit_once;
	ft_resetchooseobj(setup); // reset tous les index
}

t_color			*ft_getobjclr(t_setup *setup, t_ray ray)
{
	if (ray.obj == SPH)
		return (&OBJDEF.sphere[ray.objn].col);
	if (ray.obj == PLN)
		return (&OBJDEF.plane[ray.objn].col);
	return (&SETUP.background);
}
/*
** EXEMPLE, ici ce qui est important c'est le hitObject, en gros il faut juste que l on sache sur quoi on tape depuis l exterieur du scope de la fonction
**	bool trace(const Vec3f &orig, const Vec3f &dir, const std::vector<std::unique_ptr<Object>> &objects, float &tNear, const Object *&hitObject)
**	{
**		tNear = kInfinity;
**    std::vector<std::unique_ptr<Object>>::const_iterator iter = objects.begin();
**    for (; iter != objects.end(); ++iter) {
**        float t = kInfinity;
**        if ((*iter)->intersect(orig, dir, t) && t < tNear) {
**            hitObject = iter->get();
**            tNear = t;
**        }
**    }
**
**    return (hitObject != nullptr);
**	}
*/

static t_color	*ft_raytracecol(t_setup *setup, t_ray ray, t_color *col) //RAYCAST, retourne la couleur, remplacer par ft_cast_ray
{
  /*
	** On set la couleur a celle du fond
	** SI on rencontre un objet (fonction trace)
	** fonction trace(orig, dir, objects, t, hitObject)
	** hitObjetc ->
	** 	Alors on a besoin de :
	**	Vec3f Phit = ray.orig + ray.dir * t; -> coordonnee d origine + (direction multipliée par la distance a l origine t)
	**  Vec3f Nhit; -> la normale au point d'intrsection (/!\ c'est un vecteur normalisé MAIS la normale)
	**		pour une sphere :  Vec3f Nhit = normalize(Phit - C); avec C le centre
	**  Vec2f tex; -> la texture
	** 		les coordonnees spherique d un point sur la sphere ramppé dans sur l'intervale [0,1]
	**		coordonnes spherique:
	**			P.x=cos(θ)sin(ϕ),
	**			P.y=cos(θ),
	**			P.z=sin(θ)sin(ϕ).
	**		ou d'apres le point dans l espace cartesien
	**			ϕ=atan(z,x),
	**			θ=acos(P.yR).
	**		Avec R le rayon (radius ?) de la sphere
	** Pour eviter les soucis:
	**	"Thus the formula suffers from the effect of what we call a loss of significance. This happens for instance when b and the root of the discriminant don't have the same sign but have values very close to each other. Because of the limited numbers used to represent floating numbers on the computer, in that particular case, the numbers would either cancel out when they shouldn't (this is called catastrophic cancellation) or round off to an unacceptable error (you will easily find more
	**	information related to this topic on the internet)"
	**	hitObject->getSurfaceData(Phit, Nhit, tex); (on a initialisé le hit object dans la fonction trace)
	** 	pattern -> permet de def un dammier par exemple
	** 	hitColor = std::max(0, Nhit.dotProduct(-dir)) * mix(hitObject->color, hitObject->color * 0.8, pattern);
	** ENFIN
	** On retourne la couleur (hitColor)
	*/
	ft_primray(setup, &ray); // rayon lance a partir du point d'origine et qui permet de savoir si rayon hit et dans le cas echeant la distance et l'objet qui correspond
	if (ray.hit == ERROR)
		return (&SETUP.background);
	return (col = ft_getobjclr(setup, ray)); // permet de retourner la couleur de l'objet correspondant
}

// ft_trace(ray.orig, ray.dir, ray.size, setup /* stock les obj */, ray.hit)
t_bool ft_trace(t_ray *ray,t_setup *setup)
{
	size_t		i; // correspond au type d'objet (par example SPH = 0 et PLN = 1), on tombera donc dans les fonctions d'intersections correspondantes
	double		dist;
	t_bool		hit_once;
	double		t_near;

	i = 0;
	t_near = MAX_INT;
	hit_once = FALSE;
	while (SPH_N < NSPHERE) // ce qui permet de savoir quel est l'objet rencontre et sa fonction d'intersection
	{
		ray->hit = FALSE; // je part du principe que ca n'a pas hit
		ray->hit = OBJS->param[i].paramfunc(ray, (void *)setup);
		if (ray->hit == TRUE && ray->size < t_near)
		{
			hit_once = ray->hit;
			ray->objn = SPH_N; // permet de savoir l'index de la forme
			t_near = ray->size;
			ray->obj = i;
		}
		SPH_N++;
	}
	ft_resetchooseobj(setup); // reset tous les index
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

t_color ft_cast_ray(int i, int j, t_ray ray, t_setup *setup)
{
	t_color hit_col;

	hit_col = SETUP.background;
	if (ft_trace(&ray, setup))
	{
		t_vec3 hit_point = ft_vec3vop_r(ray.orig, ft_vec3sop_r(ray.dir, ray.size, '*'), '+');
		t_vec3 hit_nrml = ft_vec3vop_r(hit_point, OBJDEF.sphere[ray.objn].pos, '-'); // pas besoin pour l instant ?
		ft_vec3normalize(&hit_nrml);
		/*	t_vec2 hit_text; // pas besoin pour l'instant?
		ft_get_surface_data(&hit_point, &hit_nrml, &hit_text); set hit_nrml et hit_text, pour shader le point, permet meilleur calcul de la couleur
		**	// Use the normal and texture coordinates to shade the hit point.
		**	// The normal is used to compute a simple facing ratio and the texture coordinate
		**	// to compute a basic checker board pattern
		**	float scale = 4;
		**	float pattern = (fmodf(tex.x * scale, 1) > 0.5) ^ (fmodf(tex.y * scale, 1) > 0.5);
		**	hitColor = std::max(0.f, Nhit.dotProduct(-dir)) * mix(hitObject->color, hitObject->color * 0.8, pattern);
		*/
		hit_col = OBJDEF.sphere[ray.objn].col;
		t_vec3 dir_opposite = {-ray.dir.x, -ray.dir.y, -ray.dir.z};
		double shade = max(0.0, ft_dotproduct(hit_nrml, dir_opposite));
		hit_col.r *= shade;
		hit_col.g *= shade;
		hit_col.b *= shade;
	}
	return (hit_col);
}

/*
TODO Notes sur ft_cast_ray

// retourne couleur de l'objet
 on doit :
** trouver l'objet
** set la hit_color a la couleur de l'objet rencontré

// couleur degradés
// tmp = ft_vec3vop_r(ray.dir, vec, '+');
// tmp = ft_vec3sop_r(tmp, 0.5, '*');
// hit_col.r = tmp.x * 255;
// hit_col.g = tmp.y * 255;
// hit_col.b = tmp.z * 255;
*/

void multVecMatrix(t_vec3 *src, t_vec3 *dst, double **x) {
	double a, b, c, w;

	a = src->x * x[0][0] + src->y * x[1][0] + src->z * x[2][0] + x[3][0];
	b = src->x * x[0][1] + src->y * x[1][1] + src->z * x[2][1] + x[3][1];
	c = src->x * x[0][2] + src->y * x[1][2] + src->z * x[2][2] + x[3][2];
	w = src->x * x[0][3] + src->y * x[1][3] + src->z * x[2][3] + x[3][3];

	dst->x = a / w;
	dst->y = b / w;
	dst->z = c / w;
}

void multDirMatrix(t_vec3 *src, t_vec3 *dst, double **x) {
	double a, b, c;

	a = src->x * x[0][0] + src->y * x[1][0] + src->z * x[2][0];
	b = src->x * x[0][1] + src->y * x[1][1] + src->z * x[2][1];
	c = src->x * x[0][2] + src->y * x[1][2] + src->z * x[2][2];

	dst->x = a;
	dst->y = b;
	dst->z = c;
}
int			ft_raytracing(t_setup *setup) // Nathan: en fait ici c est la fonction de render
{
  // TODO CameraToWorld transfo https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays
	t_pix	pix;
	t_ray	ray;
	t_vec3 orig = {0.0, 0.0, 0.0};
	t_color	col = {255, 0, 255};
	int i;
	int j;
	double **camToWorld = ft_matrixzero(4);
	camToWorld[0][0] = 0.945519;
	camToWorld[0][1] = 0;
	camToWorld[0][2] = -0.125569;
	camToWorld[0][3] = 0;
	camToWorld[1][0] = -0.179534;
	camToWorld[1][1] = 0.834209;
	camToWorld[1][2] = -0.521403;
	camToWorld[1][3] = 0;
	camToWorld[2][0] = 0.271593;
	camToWorld[2][1] = 0.551447;
	camToWorld[2][2] = 0.78876;
	camToWorld[2][3] = 0;
	camToWorld[3][0] = 4.208271;
	camToWorld[3][1] = 8.374532;
	camToWorld[3][2] = 17.932925;
	camToWorld[3][3] = 1;
	// camToWorld[0][0] = 0;
	// camToWorld[0][1] = 0;
	// camToWorld[0][2] = 0;
	// camToWorld[0][3] = 0;
	// camToWorld[1][0] = 0;
	// camToWorld[1][1] = 0;
	// camToWorld[1][2] = 0;
	// camToWorld[1][3] = 0;
	// camToWorld[2][0] = 0;
	// camToWorld[2][1] = 0;
	// camToWorld[2][2] = 0;
	// camToWorld[2][3] = 0;
	// camToWorld[3][0] = 0;
	// camToWorld[3][1] = 0;
	// camToWorld[3][2] = 0;
	// camToWorld[3][3] = 0;

	multVecMatrix(&orig, &ray.orig, camToWorld);
	// ft_setup_cam(setup); // fonction qui permet d'initialiser la camera suivant les donnee du parser
	pix.y = -1;
	while (++pix.y < (int)SETUP.height)
	{
		pix.x = -1;
		while (++pix.x < (int)SETUP.width)
		{
			float scale = tan((90 * 0.5) * M_PI / 180);
    	float imageAspectRatio = SETUP.width / (float)SETUP.height;
			float x = (2 * (pix.y + 0.5) / (float)SETUP.width - 1) * imageAspectRatio * scale;
      float y = (1 - 2 * (pix.x + 0.5) / (float)SETUP.height) * scale;
			// MAYA
			// float x = (2 * (pix.y + 0.5) / (float)SETUP.width - 1) * scale;
      // float y = (1 - 2 * (pix.x + 0.5) / (float)SETUP.height) * scale * 1 / imageAspectRatio;
			t_vec3 dir = {x, y, -1};
			multDirMatrix(&dir, &ray.dir, camToWorld);
			ft_vec3normalize(&ray.dir);
			col = ft_cast_ray(pix.y, pix.x, ray, setup);
			// *(pix++) = castRay(orig, dir, objects, lights, options, 0);
			ft_put_pixel(setup, pix.x, pix.y, ft_colortohex(&col));
		}
	}
	return (OK);
}
