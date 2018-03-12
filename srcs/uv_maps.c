#include "../includes/rtv1.h"
#include <stdio.h>

void uv_map_sph(t_vec3 hit, t_list *form, t_col *col, t_text *text)
{
  double u;
  double v;
  t_vec3 tmp;

  tmp = ft_vec3vop_r(hit, FORM(form)->sph.ctr, '-');
  u = 0.5 + atan2(tmp.z, tmp.x) / (2 * M_PI);
  u *= text->img_w;
  tmp = ft_vec3sop_r(tmp, FORM(form)->sph.r, '/');
  v = 0.5 - asin(tmp.y) / M_PI;
  v *= text->img_h;
  // u/=4;
  // v/=4; GROSSI
  u = (int)u % 400;
  v = (int)v % 400;
  if (u < 0)
    u = u + 400;
  if (v < 0)
    v = v + 400;
  *col = text->map[(int)u + (int)v * text->img_w];
}

/*
** prend la normale et on veut deter deux vect perpendicualiree sur le plan
*/
void uv_map_pln(t_vec3 hit, t_list *form, t_col *col, t_text *text)
{
  t_vec3 nrml;
  t_vec3 u_axes;
  t_vec3 v_axes;
  double u;
  double v;
  nrml = FORM(form)->plan.nrml;
  u_axes = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(0., 1., 0.), \
				nrml, 'c'));
        // cas d erreur a gerer avec == 0
  v_axes = ft_vec3normalize_r(ft_vec3vop_r(nrml, u_axes, 'c'));
  u = ft_vec3dot(hit, u_axes);
  v = ft_vec3dot(hit, v_axes);
  // u*=4;
  // v*=4; RAPETISSI TODO refacto + scale
  u *= text->img_w;
  v *= text->img_h;
  u = (int)u % 400;
  v = (int)v % 400;
  if (u < 0)
    u = u + 400;
  if (v < 0)
    v = v + 400;
  *col = text->map[(int)u + (int)v * text->img_w];
}

void uv_map_cyl(t_vec3 hit, t_list *form, t_col *col, t_text *text)
{
  t_vec3 coord;
  t_vec3 x_axe;
  t_vec3 y_axe;
  double u;
  double v;

  hit = ft_vec3vop_r(FORM(form)->cyl.pos, hit, '-');
  coord.z = ft_vec3dot(hit, FORM(form)->cyl.dir);
  x_axe = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(0., 1., 0.), \
				FORM(form)->cyl.dir, 'c'));
  if (ft_vec3norm(x_axe) == 0.0)
    x_axe = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(1., 0., 0.), \
        FORM(form)->cyl.dir, 'c'));
  hit = ft_vec3vop_r(hit, ft_vec3sop_r(FORM(form)->cyl.dir, coord.z, '*'), '-');
  y_axe = ft_vec3vop_r(x_axe, FORM(form)->cyl.dir, 'c');
  coord.x = ft_vec3dot(hit, x_axe);
  coord.y = ft_vec3dot(hit, y_axe);
  u = atan2(coord.y, coord.x) / (2 * M_PI);
  v = coord.z;
  u *= text->img_w;
  v *= text->img_h;
  // u *=2;
  // v *= 2;
  u = (int)u % 400;
  v = (int)v % 400;
  if (u < 0)
    u = u + 400;
  if (v < 0)
    v = v + 400;
  *col = text->map[(int)u + (int)v * text->img_w];
}

void uv_map_cone(t_vec3 hit, t_list *form, t_col *col, t_text *text)
{
  t_vec3 coord;
  t_vec3 x_axe;
  t_vec3 y_axe;
  double u;
  double v;

  hit = ft_vec3vop_r(FORM(form)->cone.org, hit, '-');
  coord.z =ft_vec3dot(FORM(form)->cone.dir, hit);
  // tmp = ft_vec3normalize_r(tmp);
  // tmp = tmp * 1; //wouhahou
  // tmp = ft_vec3dot(hit, )
  x_axe = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(0., 1., 0.), \
				FORM(form)->cone.dir, 'c'));
  if (ft_vec3norm(x_axe) == 0.0)
    x_axe = ft_vec3normalize_r(ft_vec3vop_r(ft_vec3_r(1., 0., 0.), \
        FORM(form)->cone.dir, 'c'));
  hit = ft_vec3vop_r(hit, ft_vec3sop_r(FORM(form)->cone.dir, coord.z, '*'), '-');
  y_axe = ft_vec3vop_r(x_axe, FORM(form)->cone.dir, 'c');
  coord.x = ft_vec3dot(hit, x_axe);
  coord.y = ft_vec3dot(hit, y_axe);
  u = atan2(coord.y, coord.x) / (2 * M_PI);
  v = coord.z;
  u *= text->img_w;
  v *= text->img_h;
  // u *=2;
  // v *= 2;
  u = (int)u % 400;
  v = (int)v % 400;
  if (u < 0)
    u = u + 400;
  if (v < 0)
    v = v + 400;
  *col = text->map[(int)u + (int)v * text->img_w];
}
