/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 19:16:03 by ggrybova          #+#    #+#             */
/*   Updated: 2017/08/21 19:21:06 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		get_img_color(t_im *tex, int x, int y, t_col *c)
{
	c->red = tex->addr[y * tex->size_l + x * (tex->b_p_p / 8) + 2];
	c->green = tex->addr[y * tex->size_l + x * (tex->b_p_p / 8)];
	c->blue = tex->addr[y * tex->size_l + x * (tex->b_p_p / 8) + 1];
}

void		pixel_coord_img(t_im *img, int x, int y, t_col *c)
{
	img->addr[y * img->size_l + x * (img->b_p_p / 8) + 2] = c->red;
	img->addr[y * img->size_l + x * (img->b_p_p / 8)] = c->green;
	img->addr[y * img->size_l + x * (img->b_p_p / 8) + 1] = c->blue;
}

void		draw_wall(t_mlx *m, int x)
{
	t_col	c;
	int		y;
	int		d;

	m->tex_n = m->map[m->box_x][m->box_y] - 1;
	if (m->side == 0)
		m->wall_x = m->ray_py + m->wall_dist * m->ray_dy;
	else
		m->wall_x = m->ray_px + m->wall_dist * m->ray_dx;
	m->wall_x -= floor(m->wall_x);
	m->tex_x = (int)(m->wall_x * (double)(m->wall_tex[m->tex_n].w));
	if ((m->side == 0 && m->ray_dx > 0) || (m->side == 1 && m->ray_dy < 0))
		m->tex_x = m->wall_tex[m->tex_n].w - m->tex_x - 1;
	y = m->y0 - 1;
	while (++y < m->y1)
	{
		d = y * 256 - HEIGHT * 128 + m->line_height * 128;
		m->tex_y = (d * m->wall_tex[m->tex_n].h / m->line_height / 256);
		get_img_color(&m->wall_tex[m->tex_n], m->tex_x, m->tex_y, &c);
		pixel_coord_img(&m->image, x, y, &c);
	}
	m->ray_y = y;
}

void		floor_coord(t_mlx *m)
{
	double	fl_x;
	double	fl_y;
	double	d;
	double	weight;

	d = HEIGHT / (2.0 * m->ray_y - HEIGHT);
	weight = d / m->wall_dist;
	fl_x = weight * m->fl_wall_x + (1 - weight) * m->px;
	fl_y = weight * m->fl_wall_y + (1 - weight) * m->py;
	m->fl_tex_x = (int)(fl_x * m->wall_tex[3].w) % m->wall_tex[3].w;
	m->fl_tex_y = (int)(fl_y * m->wall_tex[3].h) % m->wall_tex[3].h;
}

void		draw_floor_and_ceil(t_mlx *m, int x)
{
	t_col	c;

	if (m->side == 0)
	{
		m->fl_wall_x = (m->ray_dx > 0) ? m->box_x : m->box_x + 1;
		m->fl_wall_y = m->box_y + m->wall_x;
	}
	else
	{
		m->fl_wall_y = (m->ray_dy > 0) ? m->box_y : m->box_y + 1;
		m->fl_wall_x = m->box_x + m->wall_x;
	}
	m->y1 = (m->y1 < 0) ? HEIGHT : m->y1;
	while (++m->ray_y < HEIGHT)
	{
		floor_coord(m);
		get_img_color(&m->wall_tex[3], m->fl_tex_x, m->fl_tex_y, &c);
		pixel_coord_img(&m->image, x, m->ray_y, &c);
		get_img_color(&m->wall_tex[4], m->fl_tex_x, m->fl_tex_y, &c);
		pixel_coord_img(&m->image, x, (HEIGHT - m->ray_y), &c);
	}
}
