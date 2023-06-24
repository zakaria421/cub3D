/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbentalh <zbentalh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:21:09 by zbentale          #+#    #+#             */
/*   Updated: 2023/06/24 11:58:28 by zbentalh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
// # include "../minilibx_opengl_20191021/mlx.h"
# include "float.h"
# include "get_next_line/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1400
# define HIGHT 720
# define TOLE 40
# define PLAYER_S 10
# define MINIMAP_SCALE 0.3

typedef struct s_draw
{
	int			y;
	int			z;
	int			r;
	float		l;
	float		i;
}				t_draw;

typedef struct s_hitfinder
{
	float		x;
	float		y;
	float		xstep;
	float		ystep;
}				t_hitfinder;

typedef struct s_texture
{
	void		*img;
	char		*data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			hight;
}				t_texture;

typedef struct s_test
{
	int			width;
	int			hight;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	char		*no;
	char		*so;

}				t_test;

typedef struct s_hit
{
	double		x;
	double		y;
	double		angle;
	int			vertical;
}				t_hit;

typedef struct s_player
{
	float		posx;
	float		posy;
	float		x;
	float		y;
	double		angle;
	int			a;
	int			uod;
	int			lor;
}				t_player;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_mlx;

typedef struct s_cube
{
	char		**map;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			fc;
	int			cc;
	t_player	player;
	t_mlx		mlx;
	t_test		test;
	t_texture	text[4];
}				t_cube;

typedef struct s_check
{
	int			north;
	int			south;
	int			east;
	int			west;
	int			floor;
	int			ceiling;
	int			player;
}				t_check;

typedef struct s_map
{
	char		*allin;
	char		**map;
	char		*line;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			fd;
	int			xpm;
	int			count;
	int			f;
	int			c;
	t_check		check;
}				t_map;
char			*get_next_line(int fd);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdupspace(const char *s1);
char			**ft_split(char const *s, char c);
int				close_pro(t_cube *cube);
float			calcul_c(int y, int c);
int				ft_stlen_v2(char **str, int y);
size_t			ft_double_strlen(char **s);
int				rotation(int x, int y, t_cube *cube);
int				update_player(t_cube *cube);
int				no_move(int keycode, t_cube *cube);
int				move(int keycode, t_cube *cube);
void			update_player_toward_left(t_cube *cube);
void			update_player_toward_right(t_cube *cube);
void			update_player_forward(t_cube *cube);
void			update_player_backward(t_cube *cube);
int				wall_check_test(t_cube *cube);
void			start(t_map *g);
void			my_mlx_pixel_put(t_cube *data, int x, int y, int color);
void			d_game(t_cube *cube, float i, int x, t_hit hit);
void			draw_wall(t_cube *cube, int c, int tmp_x, t_hit hit);
int				texture_color(t_cube *cube, int x, int y, int i);
void			my_mlx_pixel_put(t_cube *data, int x, int y, int color);
void			texture(t_cube *cube);
void			horizintol_hit(t_cube *cube, double angle, t_hit *hit);
void			vertical_hit(t_cube *cube, double angle, t_hit *hit);
void			step_check(double angle, float *xstep, float *ystep);
t_hit			*hit_init(t_hit *hit, double angle);
t_hitfinder		y_and_ystep(t_cube *cube, t_hitfinder h, double angle);
t_hitfinder		x_and_xstep(t_cube *cube, t_hitfinder h, double angle);
t_hitfinder		finder_init(void);
t_hit			*distance_calcu(t_cube *cube, t_hit *hit, t_hitfinder h);
t_hitfinder		y_and_ystep_vertical(t_cube *cube, double angle, t_hitfinder h);
t_hitfinder		x_and_xstep_vertical(t_cube *cube, double angle, t_hitfinder h);
size_t			ft_double_strlen(char **s);
#endif