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

static void		ft_primray(t_setup *setup, t_ray *ray)
{
	size_t		i; // correspond au type d'objet (par example SPH = 0 et PLN = 1), on tombera donc dans les fonctions d'intersections correspondantes
	double		dist;
	t_bool		hit_once;

	i = 0;
	hit_once = ERROR; // je part du principe que ca n'a pas hit
	ray->size = MAX_INT; // j'initialise a distance infinie
	while (ft_chooseobj(setup, &i) == OK) // ce qui permet de savoir quel est l'objet rencontre et sa fonction d'intersection
	{
		ray->hit = OBJS->param[i].paramfunc((void *)setup, *ray, &dist); // va dans la fonction d'intersection correspondante, quand i = 0, va dans ft_sphere_intersection, retourne si hit ou pas et donne la distance.
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
*/

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

static t_color	*ft_raytracecol(t_setup *setup, t_ray ray, t_color *col) //RAYCAST, retourne la couleur
{
  /*
	** On set la couleur a celle du fond
	** SI on rencontre un objet (fonction trace)
	** fonction trace(orig, dir, objects, t, hitObject)
	** hitObjetc ->
	** 	Alors on a besoin de :
	**	Vec3f Phit = orig + dir * t; -> coordonnee d origine + (direction multipliée par la distance a l origine t)
	**  Vec3f Nhit; -> la normale au point d'intrsection (/!\ c'est un vecteur normalisé MAIS la normale)
	**  Vec2f tex; -> la texture
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

int			ft_raytracing(t_setup *setup) // Nathan: en fait ici c est la fonction de render
{
	t_pix	pix;
	t_ray	ray;
	t_color	col;

	pix.y = -1;
	ft_setup_cam(setup); // fonction qui permet d'initialiser la camera suivant les donnee du parser
	while (++pix.y < (int)SETUP.height)
	{
		pix.x = -1;
		while (++pix.x < (int)SETUP.width)
		{
			/* ICI on a besoin de l origine de la camera, CAM.pos
			** de la direction du rayon lancer calculer comme suit:
			** float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
      ** float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;
			** ray.dir = normalize(Vec3f(x,y,-1) - Vec3f(0));
			** ENSUITE on doit transformer le rayon de ses coordonnées screen au coord world //Tu as deja géré ca ?
			** ENFIN on appelle la fonction RayCast qui nous donnera la couleur
      ** RayCast prend en arg: origine, direction, objets (forme geo)
			*/
			ray = ft_raycalcforpix(setup, pix); // permet de return la direction du rayon caste suivant le pixel et la config de la cam
			ft_put_pixel(setup, pix.x, pix.y, \
					ft_colortohex(ft_raytracecol(setup, ray, &col))); // ft_raytracecol permet de faire les operation de calcul de la couleur avec le raytrace
		}
	}
	return (OK);
}
