/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_labyrinth.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 19:00:04 by ggrybova          #+#    #+#             */
/*   Updated: 2017/08/21 19:20:46 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		distance_to_side(t_mlx *m, int x)
{
	m->camera = 2 * x / (double)WIDTH - 1;
	m->ray_px = m->px;
	m->ray_py = m->py;
	m->ray_dx = m->dx + m->plane_x * m->camera;
	m->ray_dy = m->dy + m->plane_y * m->camera;
	m->box_x = (int)m->ray_px;
	m->box_y = (int)m->ray_py;
	m->dside_x = sqrt(1 + pow(m->ray_dy / m->ray_dx, 2));
	m->dside_y = sqrt(1 + pow(m->ray_dx / m->ray_dy, 2));
	m->wall = 0;
	m->step_x = (m->ray_dx < 0) ? -1 : 1;
	m->step_y = (m->ray_dy < 0) ? -1 : 1;
	if (m->ray_dx < 0)
		m->side_x = (m->ray_px - m->box_x) * m->dside_x;
	else
		m->side_x = (m->box_x + 1.0 - m->ray_px) * m->dside_x;
	if (m->ray_dy < 0)
		m->side_y = (m->ray_py - m->box_y) * m->dside_y;
	else
		m->side_y = (m->box_y + 1.0 - m->ray_py) * m->dside_y;
}

void		distance_to_wall(t_mlx *m)
{
	while (m->wall == 0)
	{
		if (m->side_x < m->side_y)
		{
			m->side_x += m->dside_x;
			m->box_x += m->step_x;
			m->side = 0;
		}
		else
		{
			m->side_y += m->dside_y;
			m->box_y += m->step_y;
			m->side = 1;
		}
		if (m->map[m->box_x][m->box_y] > 0)
			m->wall = 1;
	}
	if (m->side == 0)
		m->wall_dist = (m->box_x - m->ray_px + (1 - m->step_x) / 2 != 0) ?
				(m->box_x - m->ray_px + (1 - m->step_x) / 2) / m->ray_dx : 0;
	else
		m->wall_dist = ((m->box_y - m->ray_py + (1 - m->step_y) / 2)) ?
				(m->box_y - m->ray_py + (1 - m->step_y) / 2) / m->ray_dy : 0;
}

void		finish(t_mlx *m, int x)
{
	m->line_height = abs((int)(HEIGHT / m->wall_dist));
	m->y0 = -m->line_height / 2 + HEIGHT / 2;
	if (m->y0 < 0)
		m->y0 = 0;
	m->y1 = m->line_height / 2 + HEIGHT / 2;
	if (m->y1 >= HEIGHT)
		m->y1 = HEIGHT - 1;
	draw_wall(m, x);
	draw_floor_and_ceil(m, x);
}

int			create_labyrinth(t_mlx *m)
{
	int		x;

	m->image.im = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	m->image.addr = mlx_get_data_addr(m->image.im, &(m->image.b_p_p),
					&(m->image.size_l), &(m->image.end));
	x = -1;
	while (++x < WIDTH)
	{
		distance_to_side(m, x);
		distance_to_wall(m);
		finish(m, x);
	}
	mlx_put_image_to_window(m->mlx, m->win, m->image.im, 0, 0);
	mlx_destroy_image(m->mlx, m->image.im);
	return (1);
}
