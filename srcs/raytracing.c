/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 14:49:45 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/13 16:11:21 by psebasti         ###   ########.fr       */
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

static t_color	*ft_raytracecol(t_setup *setup, t_ray ray, t_color *col)
{
	ft_primray(setup, &ray); // rayon lance a partir du point d'origine et qui permet de savoir si rayon hit et dans le cas echeant la distance et l'objet qui correspond
	if (ray.hit == ERROR)
		return (&SETUP.background);
	return (col = ft_getobjclr(setup, ray)); // permet de retourner la couleur de l'objet correspondant
}

int			ft_raytracing(t_setup *setup)
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
			ray = ft_raycalcforpix(setup, pix); // permet de return la direction du rayon caste suivant le pixel et la config de la cam
			ft_put_pixel(setup, pix.x, pix.y, \
					ft_colortohex(ft_raytracecol(setup, ray, &col))); // ft_raytracecol permet de faire les operation de calcul de la couleur avec le raytrace
		}
	}
	return (OK);
}
