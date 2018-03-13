#include "../includes/rtv1.h"

void uv_map_sph(t_vec3 hit, t_list *form, t_col *col, t_text *text)
{
  double u;
  double v;
  t_vec3 tmp;

  tmp = ft_vec3vop_r(hit, FORM(form)->sph.ctr, '-');
  u = 0.5 + atan2(tmp.z, tmp.x) / (2 * M_PI);
  tmp = ft_vec3sop_r(tmp, FORM(form)->sph.r, '/');
  v = 0.5 - asin(tmp.y) / M_PI;
  fit_and_scale(&u, &v, text);
  *col = text->map[(int)u + (int)v * text->img_w];
}

/*
** prend la normale et on veut deter deux vect perpendicualiree sur le plan
*/
void uv_map_pln(t_vec3 hit, t_list *form, t_col *col, t_text *text)
{
  t_vec3 x_axe;
  t_vec3 y_axe;
  double u;
  double v;

  x_axe = get_x_axe(FORM(form)->plan.nrml);
  y_axe = ft_vec3normalize_r(ft_vec3vop_r(x_axe, FORM(form)->plan.nrml, 'c'));
  u = ft_vec3dot(hit, x_axe);
  v = ft_vec3dot(hit, y_axe);
  fit_and_scale(&u, &v, text);
  *col = text->map[(int)u + (int)v * text->img_w];
}

void uv_map_cyl(t_vec3 hit, t_list *form, t_col *col, t_text *text)
{
  double u;
  double v;
  t_vec3 coord;

  get_obj_space_coords(hit, &coord, FORM(form)->cyl.pos, FORM(form)->cyl.dir);
  u = atan2(coord.y, coord.x) / (2 * M_PI);
  v = coord.z;
  fit_and_scale(&u, &v, text);
  *col = text->map[(int)u + (int)v * text->img_w];
}

void uv_map_cone(t_vec3 hit, t_list *form, t_col *col, t_text *text)
{
  t_vec3 coord;
  double u;
  double v;

  get_obj_space_coords(hit, &coord, FORM(form)->cone.org, FORM(form)->cone.dir);
  u = atan2(coord.y, coord.x) / (2 * M_PI);
  v = coord.z;
  fit_and_scale(&u, &v, text);
  *col = text->map[(int)u + (int)v * text->img_w];
}
