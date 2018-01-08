/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 19:26:51 by ggrybova          #+#    #+#             */
/*   Updated: 2017/11/14 13:04:22 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define WIDTH 640
# define HEIGHT 480
# include "libft/libft.h"
# include "minilibx_macos/mlx.h"
# include <math.h>

typedef struct	s_im
{
	int			w;
	int			h;
	void		*im;
	char		*addr;
	int			b_p_p;
	int			size_l;
	int			end;
}				t_im;

typedef struct	s_col
{
	int			red;
	int			green;
	int			blue;
	int			c;
}				t_col;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;

	int			map_width;
	int			map_height;
	int			map[24][24];

	double		px;
	double		py;
	double		dx;
	double		dy;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	t_im		*wall_tex;
	t_im		image;

	double		camera;
	double		ray_px;
	double		ray_py;
	double		ray_dx;
	double		ray_dy;
	double		dside_x;
	double		dside_y;
	double		side_x;
	double		side_y;
	double		wall_dist;
	int			box_x;
	int			box_y;
	int			wall;
	int			side;
	int			step_x;
	int			step_y;
	int			line_height;
	int			y0;
	int			y1;

	int			tex_n;
	int			tex_x;
	int			tex_y;
	double		wall_x;
	double		fl_wall_x;
	double		fl_wall_y;
	int			fl_tex_x;
	int			fl_tex_y;
	int			ray_y;
	int			music;
}				t_mlx;

void			fill_map(t_mlx *m);
void			fill_data(t_mlx *m);
int				create_labyrinth(t_mlx	*m);
void			get_img_color(t_im *tex, int x, int y, t_col *c);
void			pixel_coord_img(t_im *img, int x, int y, t_col *c);
void			draw_wall(t_mlx *m, int x);
void			draw_floor_and_ceil(t_mlx *m, int x);
int				hook_func(int key, t_mlx *m);
void			*mlx_init();
int				hook_func2(t_mlx *m);

#endif
