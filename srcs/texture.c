#include "../includes/rtv1.h"

t_col get_px_color(SDL_PixelFormat *fmt, Uint32 pixel)
{
	t_col color;
	Uint32 temp;
	/* Get Red component */
	temp = pixel & fmt->Rmask;  /* Isolate red component */
	temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
	color.r = (Uint8)temp / 255.0;

	/* Get Green component */
	temp = pixel & fmt->Gmask;  /* Isolate green component */
	temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
	color.g = (Uint8)temp / 255.0;

	/* Get Blue component */
	temp = pixel & fmt->Bmask;  /* Isolate blue component */
	temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
	temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
	color.b = (Uint8)temp / 255.0;

	/* Get Alpha component */
	// temp = pixel & fmt->Amask;  /* Isolate alpha component */
	// temp = temp >> fmt->Ashift; /* Shift it down to 8-bit */
	// temp = temp << fmt->Aloss;  /* Expand to a full 8-bit number */
	// alpha = (Uint8)temp;
	// printf("Pixel Color -> R: %f,  G: %f,  B: %f", color.r, color.g, color.b);
	return color;
}

/*
 * Return the pixel value at (x, y)
 * NOTE: The surface must be locked before calling this!
 * https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideo.html#AEN90
 * TODO voir si on vire pas ca etant donné qu on peut imposer un type d img
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;

		default:
			return 0;       /* shouldn't happen, but avoids warnings */
	}
}

void cpy_px_map(t_text *texture, SDL_Surface *img)
{
	Uint32 pixel;
	int x;
	int y;

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
/*
 ** potentiellement utile
 ** SDL_PixelFormat* pixelFormat = img->format;
 ** Uint32 pixelFormatEnum = pixelFormat->format;
 ** read_img(img);
 ** const char* surfacePixelFormatName = SDL_GetPixelFormatName(pixelFormatEnum);
 ** SDL_Log("The surface's pixelformat is %s", surfacePixelFormatName);
 **
 ** Check the bitdepth of the surface
 ** printf("%d bits pxl\n", img->format->BitsPerPixel);
 */
t_text *get_texture_datas(char *path)
{
	SDL_Surface *img;
	t_text  *texture;

	img = NULL;
	if (!(texture = malloc(sizeof(t_text))))
		exit(1);
	if (!(img = SDL_LoadBMP(path)))
	{
		printf("load failed\n");
		free(texture);
		exit (1);
	}
	else
	{
		texture->img_w = img->w;
		texture->img_h = img->h;
		if(!(texture->map = malloc(sizeof(t_col) * (img->w * img->h))))
			exit(1);
		SDL_LockSurface(img);
		cpy_px_map(texture, img);
		SDL_UnlockSurface(img);
		SDL_FreeSurface(img);
	}
	return (texture);
}

t_mat		get_mat_at(t_vec3 hit, t_list *form, t_mat mat_obj)
{
	t_mat	hit_mat;
	t_text	*text;

	hit_mat = mat_obj;
	if (mat_obj.text > 0 && mat_obj.text <= NUM_TEXT)
	{
		text = get_st()->textures[mat_obj.text - 1];
		uv_map()[FORM(form)->type - 1](hit, form, &hit_mat.col, text);
	}
	if (mat_obj.text > NUM_TEXT && mat_obj.text <= (NUM_TEXT + NUM_PROC))
		effects()[mat_obj.text - 1](hit, &hit_mat.col);
	return (hit_mat);
}
