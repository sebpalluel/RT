/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_manager.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeilles <mbeilles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:58:16 by mbeilles          #+#    #+#             */
/*   Updated: 2018/03/30 18:05:16 by mbeilles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_HANDLER_H
# define SDL_HANDLER_H

# include <SDL.h>
# include "libft.h"

#define DEFAULT_WIDTH	3840
#define DEFAULT_HEIGHT	2160

#define DEFAULT_WIN_W	1920
#define DEFAULT_WIN_H	1080

/*
** =============================================================================
** 						Post proccess
** =============================================================================
*/

typedef enum			e_post_effect
{
	PP_SEPIA = 0,
	PP_CELL_SHADING,
	PP_NEGATIVE,
	PP_BLACK_WHITE,
	PP_BLUR,
	PP_MAX
}						t_post_effect;


SDL_Surface				*ft_sepia(SDL_Surface *s);
SDL_Surface				*ft_cel_shading(SDL_Surface *s);
SDL_Surface				*ft_negative(SDL_Surface *s);
SDL_Surface				*ft_blackandwhite(SDL_Surface *s);
SDL_Surface				*ft_blur(SDL_Surface *s);

/*
** =============================================================================
** 						Display
** =============================================================================
*/

typedef enum			e_frame_state
{
	FS_DIRTY = 0,		// Frame is dirty and to be calculated
	FS_CALCULATING,		// Frame is in the proccess of calculation
	FS_DONE,			// Frame is raytraced
	FS_PROCCESSED,		// Post-proccess has been applied to the frame
	FS_MAX				// Max value of frame states
}						t_frame_state;

typedef struct			s_rect
{
	uint32_t			x;
	uint32_t			y;
	uint32_t			w;
	uint32_t			h;
}						t_rect;

typedef struct			s_cam
{
	t_vec3				org;
	t_vec3				frt;
	t_vec3				rgt;
	t_vec3				dwn;
	SDL_Surface			**frames;
	uint32_t			*frames_state;
	uint32_t			frame_number;
	double				perspective_factor;
	double				ambient_light;
	double				exposition;
	t_post_effect		effect;
}						t_cam;

typedef struct			s_scene
{
	t_list				*forms;
	t_list				*lgts;
	t_list				*cams;
	t_cam				*cur_cam;
	size_t				cam_n;
	double				move_step;
	double				rot_step;
	uint64_t			refr_max;
	uint64_t			refl_max;
	t_col				background;
}						t_scene;

typedef struct			s_window_data
{
	int32_t				x;
	int32_t				y;
	int32_t				w;
	int32_t				h;
	char				*title;
	uint32_t			flags;
}						t_window_data;

typedef struct			s_window
{
	SDL_Window			*window;
	SDL_Surface			*surface;
	t_scene				*scene;
	t_window_data		original_data;
	pthread_t			*thread;
	struct s_window		*next;
}						t_window;

typedef struct			s_display_manager
{
	t_window			*win;
	t_window			*cli;
	uint32_t			windows_managed;
	t_window			window_focused;
}						t_display_manager;

typedef struct			s_draw_data
{
	t_cam				*cam;
	t_scene				*scene;
	t_window			*window;
}						t_draw_data;

void					init_cam_buffers(t_cam *cam, uint32_t frames);
t_display_manager		*create_display_manager(void);
inline uint32_t			get_pixel(SDL_Surface *s, uint32_t x, uint32_t y);
inline void				set_pixel(SDL_Surface *s, uint32_t x, uint32_t y
									, uint32_t pixel);

inline t_window			*create_dwindow(t_window_data data);
inline void				destroy_dwindow(t_window *window);
inline void				create_cli(void);

void					apply_post_effect(t_cam *cam, t_post_effect e);

extern t_display_manager		g_display_manager;
t_display_manager				g_display_manager = (t_display_manager)
{
	.win = NULL,
	.cli = NULL,
	.window_focused = NULL,
	.windows_managed = 0
};

#endif
