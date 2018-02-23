/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_struct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 19:31:09 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/23 16:02:50 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_STRUCT_H
# define LIBFT_STRUCT_H

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef char		t_bool;

typedef struct		s_str
{
	char			c;
	struct s_str	*next;
}					t_str;

typedef	struct		s_fd
{
	int				fd;
	int				pos;
	char			*path;
	char			*name;
	t_str			*buffer;
	int				flags;
	int				rights;
}					t_fd;

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_vec3u
{
	size_t			x;
	size_t			y;
	size_t			z;
}					t_vec3u;

typedef struct		s_pix
{
	int				x;
	int				y;
	int				z;
}					t_pix;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

typedef struct		s_col
{
	double			r;
	double			g;
	double			b;
	double			s;
}					t_col;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*image;
	char			*image_addr;
}					t_mlx;

typedef struct		s_img
{
	void			*image;
	void			*image_addr;
	int				bbp;
	int				endian;
	int				size_x;
}					t_img;

#endif
