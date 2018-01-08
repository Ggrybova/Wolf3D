/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 18:49:00 by ggrybova          #+#    #+#             */
/*   Updated: 2017/09/23 14:28:36 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			main(int argc, char **argv)
{
	t_mlx	*m;

	if (argc != 1)
	{
		ft_putstr("Dude, don't enter an argument 8)\n");
		exit(0);
	}
	**argv = 1;
	m = (t_mlx *)ft_memalloc(sizeof(t_mlx));
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "wolf3d");
	m->map_height = 24;
	m->map_width = 24;
	m->music = 0;
	fill_map(m);
	fill_data(m);
	create_labyrinth(m);
	mlx_hook(m->win, 2, 5, hook_func, m);
	mlx_hook(m->win, 17, 1L << 17, hook_func2, m);
	mlx_loop(m->mlx);
	return (1);
}
