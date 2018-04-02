#include "../includes/rtv1.h"

t_col	get_px_color(SDL_PixelFormat *fmt, Uint32 pixel)
{
	t_col color;
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 s;

	SDL_GetRGBA(pixel, fmt, &r, &g, &b, &s);
	color.r = r / 255.0;
	color.g = g / 255.0;
	color.b = b / 255.0;
	color.s = s / 255.0;
	return (color);
}

Uint32	getpixel(SDL_Surface *surface, int x, int y)
{
	int		bpp;
	Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
	{
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	}
	else if (bpp == 4)
		return (*(Uint32 *)p);
	else
		return (0);
}

void	cpy_px_map(t_text *texture, SDL_Surface *img)
{
	Uint32	pixel;
	int		x;
	int		y;

	(void)texture;
	y = 0;
	x = 0;
	pixel = 0;
	while (x < img->w)
	{
		while (y < img->h)
		{
			pixel = getpixel(img, x, y);
			texture->map[x + y * img->w] = get_px_color(img->format, pixel);
			y++;
		}
		y = 0;
		x++;
	}
}

t_text	*get_texture_datas(char *path)
{
	SDL_Surface	*img;
	t_text		*texture;

	img = NULL;
	if (!(texture = malloc(sizeof(t_text))))
		exit(1);
	if (!(img = IMG_Load(path)))
	{
		printf("load failed\n");
		free(texture);
		exit(1);
	}
	else
	{
		texture->img_w = img->w;
		texture->img_h = img->h;
		if (!(texture->map = malloc(sizeof(t_col) * (img->w * img->h))))
			exit(1);
		SDL_LockSurface(img);
		cpy_px_map(texture, img);
		SDL_UnlockSurface(img);
		SDL_FreeSurface(img);
	}
	return (texture);
}

t_mat	get_mat_at(t_vec3 hit, t_list *form, t_mat mat_obj)
{
	t_mat	hit_mat;
	t_text	*text;
	t_col	prev_col;

	hit_mat = mat_obj;
	if (FORM(form)->type < NUM_FORM - 1) // TODO bypass torus and moebius
	{
		if (mat_obj.text_m == M_TEX)
		{
			text = get_st()->textures[mat_obj.text_c.text_num];
			uv_map()[FORM(form)->type - 1](hit, form, &hit_mat, text);
		}
		if (mat_obj.text_m == M_GEN && mat_obj.gen.mode < NUM_PROC)
		{
			prev_col = hit_mat.col;
			hit = uv_map()[FORM(form)->type - 1](hit, form, &hit_mat, text);
			hit_mat.col = ft_colinterpol(hit_mat.col, ft_col_r(0., 0., 0., 1.),
					effects()[mat_obj.gen.mode](hit, mat_obj.gen));
		}
	}
	if (FORM(form)->mat.trsp != 0)
		hit_mat.trsp = FORM(form)->mat.trsp;
	return (hit_mat);
}
