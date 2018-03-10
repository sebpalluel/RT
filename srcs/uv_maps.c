#include "../includes/rtv1.h"

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
  v_axes = ft_vec3normalize_r(ft_vec3vop_r(nrml, u_axes, 'c'));
  u = ft_vec3dot(hit, u_axes) * text->img_w;
  v = ft_vec3dot(hit, v_axes) * text->img_h;
  // u*=4;
  // v*=4; RAPETISSI
  u = (int)u % 400;
  v = (int)v % 400;
  if (u < 0)
    u = u + 400;
  if (v < 0)
    v = v + 400;
  *col = text->map[(int)u + (int)v * text->img_w];
}
