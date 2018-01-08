/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 19:21:22 by ggrybova          #+#    #+#             */
/*   Updated: 2017/11/13 15:41:21 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		music(int key, t_mlx *m)
{
	key = 0;
	if (m->music == 0)
	{
		system("afplay ./music/1.mp3&");
		m->music = 1;
	}
	else
	{
		system("killall afplay 2&>/dev/null >/dev/null");
		m->music = 0;
	}
}

void		turn(int key, t_mlx *m)
{
	double	old_dx;
	double	old_plane_x;
	double	speed;

	speed = (key == 123) ? m->rot_speed : -m->rot_speed;
	old_dx = m->dx;
	m->dx = m->dx * cos(speed) - m->dy * sin(speed);
	m->dy = old_dx * sin(speed) + m->dy * cos(speed);
	old_plane_x = m->plane_x;
	m->plane_x = m->plane_x * cos(speed) - m->plane_y * sin(speed);
	m->plane_y = old_plane_x * sin(speed) + m->plane_y * cos(speed);
}

int			hook_func2(t_mlx *m)
{
	if (m->music == 1)
		system("killall afplay 2&>/dev/null >/dev/null");
	exit(1);
	return (0);
}

int			hook_func(int key, t_mlx *m)
{
	if (key == 53)
	{
		system("killall afplay 2&>/dev/null >/dev/null");
		exit(1);
	}
	if (key == 126)
	{
		if ((m->map[(int)(m->px + m->dx)][(int)(m->py)]) == 0)
			m->px = m->px + m->dx * m->move_speed;
		if ((m->map[(int)(m->px)][(int)(m->py + m->dy)]) == 0)
			m->py = m->py + m->dy * m->move_speed;
	}
	if (key == 125)
	{
		if ((m->map[(int)(m->px - m->dx)][(int)(m->py)]) == 0)
			m->px = m->px - m->dx * m->move_speed;
		if ((m->map[(int)(m->px)][(int)(m->py - m->dy)]) == 0)
			m->py = m->py - m->dy * m->move_speed;
	}
	if (key == 123 || key == 124)
		turn(key, m);
	if (key == 49)
		music(key, m);
	create_labyrinth(m);
	return (1);
}
