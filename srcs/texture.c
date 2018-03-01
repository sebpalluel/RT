#include "../includes/rtv1.h"
#include <stdio.h>

t_col get_px_color(SDL_PixelFormat *fmt, Uint32 pixel)
{
  t_col color;
  Uint32 temp;
  /* Get Red component */
  temp = pixel & fmt->Rmask;  /* Isolate red component */
  temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
  temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
  color.r = (Uint8)temp / 255;

  /* Get Green component */
  temp = pixel & fmt->Gmask;  /* Isolate green component */
  temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
  temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
  color.g = (Uint8)temp / 255;

  /* Get Blue component */
  temp = pixel & fmt->Bmask;  /* Isolate blue component */
  temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
  temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
  color.b = (Uint8)temp / 255;

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
 *
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


void img_manipulation(void)
{
  SDL_Surface *img;
  t_col color;
  img = NULL;
  if (!(img = SDL_LoadBMP("./textures/green400x400.bmp")))
    printf("load failed\n");
  else
  {
    // SDL_PixelFormat* pixelFormat = img->format;
    // Uint32 pixelFormatEnum = pixelFormat->format;
    // read_img(img);
    // const char* surfacePixelFormatName = SDL_GetPixelFormatName(pixelFormatEnum);
    // SDL_Log("The surface's pixelformat is %s", surfacePixelFormatName);

    /* Check the bitdepth of the surface */
    // printf("%d bits pxl\n", img->format->BitsPerPixel);
    SDL_LockSurface(img);
    Uint32 pixel;

    for(int x =0; x < img->w; x++){
      for(int y = 0; y < img->h; y++){
        pixel = getpixel(img, x, y);
        color = get_px_color(img->format, pixel);
      }
    }
    SDL_UnlockSurface(img);
    SDL_FreeSurface(img);
  }
  exit(0);
}
