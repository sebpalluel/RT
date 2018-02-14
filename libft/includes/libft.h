/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psebasti <sebpalluel@free.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 15:50:29 by psebasti          #+#    #+#             */
/*   Updated: 2018/02/14 17:59:38 by psebasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <strings.h>
# include <math.h>
# include <errno.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <time.h>
# include <signal.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../../minilibx/mlx.h"
# include "libft_struct.h"
# include "libft_define.h"

int				get_next_line(const int fd, char **line);
void			ft_swap(void *a, void *b, size_t nbytes);
void			ft_perror(char *name, char *error, int exit_f);
int				match(char *s1, char *s2);
int				nmatch(char *s1, char *s2);

void			ft_colorcpy(t_color *clr_from, t_color *clr_to);
void			ft_color(t_color *clr, \
				unsigned char r, unsigned char g, unsigned char b);
t_color			*ft_colornew(unsigned char r, unsigned char g, \
				unsigned char b);
t_color			*ft_colorparse(char *arg);
t_color			*ft_hexcolor(int hexvalue);
void			ft_hextocolor(t_color *col, int hexvalue);
int				ft_colortohex(t_color *col);
void			ft_mlxdelete(t_mlx *mlx, t_img *img);
void			ft_imgclean(t_img *img, size_t width, size_t height);
void			ft_imgdel(t_img *img, void *mlx);
t_img			*ft_imgnew(void *mlx, size_t x, size_t y);
t_img			*ft_xmpnew(void *mlx, char *xmp, size_t x, size_t y);
t_mlx			*ft_initwindow(char *name, size_t width, size_t height);
void			ft_matrixadd(double **mat, double **m, double **n, int size);
void			ft_matrixhomothety(double **mat, int factor);
void			ft_matrixmult(double **mat, double **m, double **n, int size);
void			ft_matrixonpoint(double **mat, t_vec3 *vec3);
void			ft_matrixrotx(double **mat, double deg);
void			ft_matrixroty(double **mat, double deg);
void			ft_matrixrotz(double **mat, double deg);
void			ft_matrixtranslate(double **mat, t_vec3 *vec);
double			**ft_matrixzero(int size);
void			ft_pixcpy(t_pix *pix_from, t_pix *pix_to);
t_pix			*ft_pixnew(int x, int y, int z);
void			ft_pixpopulate(t_pix *to_pix, int x, int y, int z);
void			ft_vec3cpy(t_vec3 *vec_from, t_vec3 *vec_to);
t_vec3			*ft_vec3new(double x, double y, double z);
t_vec3			ft_vec3_r(double x, double y, double z);
void			ft_vec3populate(t_vec3 *to_vec3, double x, double y, double z);
void			ft_vec3vop(t_vec3 *to_vec3, t_vec3 a, t_vec3 b, char c);
void			ft_vec3sop(t_vec3 *to_vec3, t_vec3 from_vec3, double x, char c);
t_vec3			ft_vec3sop_r(t_vec3 from_vec3, double x, char c);
t_vec3			ft_vec3vop_r(t_vec3 a, t_vec3 b, char c);
void			ft_vec3normalize(t_vec3 *to_vec3);
double			ft_vec3dist(t_vec3 p1, t_vec3 p2);
t_vec3			ft_vec3unit(t_vec3 from);
t_vec3			ft_vec3add3(t_vec3 a, t_vec3 b, t_vec3 c);
double			ft_dotproduct(t_vec3 a, t_vec3 b);
float			ft_sqrtf(float n);
double			ft_invsqrt(double number);
int				ft_mlx_keytoint(int keycode);
char			ft_mlx_keytonumchar(int keycode);
char			ft_mlx_keytoletterchar(int keycode);
char			ft_mlx_printkeytochar(int keycode);

void			ft_putchar(char c);
void			ft_putendl(char const *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr(char const *s);
void			ft_putstr_fd(char const *s, int fd);

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isint(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_ishexa(int c);
int				ft_checkint(char *str);
int				ft_checkdigit(char *str);
int				ft_checkhexa(char *str);
int				ft_checkalnum(char *str);

int				ft_atoi(const char *str);
double			ft_atof(const char *str);
char			*ft_itoa(int n);
char			*ft_ftoa(float f);
int				ft_sqrt(int nb);
int				ft_pow(int n, int p);
int				ft_abs(int a);
double			ft_range_num(double input, double i[2], double o[2]);

size_t			ft_tablen(char **tab);
int				ft_tabdepth(void **tab);
void			ft_h_flip(void **array, size_t columns, size_t rows,\
				size_t nbytes);
void			ft_v_flip(void **array, size_t columns, size_t rows,\
				size_t nbytes);
int				**ft_tabintcpy(int **array, size_t width);
char			**ft_tabstrcpy(char **str);
void			ft_tabfree(void **tab);
void			ft_tabnullfree(void ***tab);
char			*ft_tabtostr(char **tab);
size_t			**ft_tabnewsize_t(size_t width, size_t height);
int				**ft_tabnewint(size_t width, size_t height);
char			**ft_tabnewstr(size_t width, size_t height);
char			***ft_tab3newstr(size_t width, size_t height);
void			ft_tab3free(void ***tab);

char			*ft_strcat(char *src, const char *dest);
char			*ft_strchr(const char *src, int c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *src);
size_t			ft_strlen(const char *s);
char			*ft_straddchar(char *src, char c);
char			*ft_strncat(char *dest, const char *src, size_t n);
char			*ft_strncpy(char *s1, const char *s2, size_t n);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *str, const char *tofind);
char			*ft_strstrn(const char *str, const char *tofind, \
		size_t occur_n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *src);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const*s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strjoinfree(char *s1, char *s2, size_t mode);
char			*ft_strnjoin(char const *s1, char const *s2, size_t len);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			**ft_strsplitequ(char const *s, char *str);
unsigned long	ft_stoul(const char *str, int base);
long int		ft_strtol(const char *str, int base);
int				ft_stroneof(char c, char *str);

int				ft_intmin(int *array, size_t size);
int				ft_intmax(int *array, size_t size);
size_t			ft_intlen(int nbr);
int				*ft_intdup(int *array, size_t width);
int				ft_getnbr(char *str);

void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memmove(void *s1, const void *s2, size_t n);
void			*ft_memset(void *b, int c, size_t len);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			ft_bzero(void *s, size_t n);
void			ft_bzerotab(void **tab);
void			*ft_memdup(const void *mem, size_t size);

t_list			*ft_lstnew(void const *content, size_t content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdelif(t_list **alst, void *to_cmpr, \
		int (*cmp)(void *, void *), void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstaddend(t_list **alst, t_list *new);
void			ft_lstaddfront(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int				ft_lstlen(t_list *lst);
void			ft_lstfree(t_list **lst);
void			**ft_lsttoarray(t_list *lst);
t_list			*ft_lstpushback(t_list **alst, void *data, size_t content_size);
t_list			*ft_lstpushfront(t_list **alst, void *data, \
		size_t content_size);
void			ft_lstaddback(t_list **alst, t_list *new);

void			ft_printfloatmatrix(float **mat, size_t size);
void			ft_printintarray(int **map, size_t width, size_t height);
void			ft_printsize_tarray(size_t **map, size_t width, size_t height);
void			ft_printstrarray(char **array);

unsigned int	ft_ror(const unsigned int value, int shift);
unsigned int	ft_rol(const unsigned int value, int shift);
uint32_t		ft_hash32(uint32_t val);
unsigned long	ft_hash(unsigned char *str);
uintmax_t		ft_rand(void);
uintmax_t		ft_randint(size_t length);
uintmax_t		ft_random(uintmax_t min, uintmax_t max, uintmax_t res);

size_t			ft_create_file(t_fd *fd, int chmod);
size_t			ft_open(t_fd *fd, int flags, int rights);
int				ft_close(t_fd *fd);
void			ft_fd_delete(t_fd *fd);

#endif
