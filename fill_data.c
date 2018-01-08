/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggrybova <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 19:10:12 by ggrybova          #+#    #+#             */
/*   Updated: 2017/11/14 13:12:12 by ggrybova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		fill_map(t_mlx *m)
{
	int		i;
	int		j;
	int		k;
	char	*l;

	i = -1;
	j = -1;
	k = -1;
	l = "11111111111111111111111110000000000000000111111110000000000000000000\
00011000000000000000020111011002222220000000022101011002222200000000020101011\
00222020000222322010001100232020000200000010111100000000000232200010001100000\
00000000000001010110000222200000002221010110000000000000003001010110000000200\
00000200100011000200000000000220101011100000000000000220101011000000232223220\
22010101100000020111111022011101100000020000000000010001110022220121111211110\
11110002222200020000010010110002000002220000010010110002201022200000000000110\
0000010000000000110101111111111111111111111111";
	while (++i < m->map_height)
	{
		j = -1;
		while (++j < m->map_width)
			m->map[i][j] = (l[++k]) - '0';
	}
}

void		create_texture(t_mlx *m)
{
	m->wall_tex[0].im = mlx_xpm_file_to_image(m->mlx, "texture/greywall.xpm",
						&m->wall_tex[0].w, &m->wall_tex[0].h);
	m->wall_tex[0].addr = mlx_get_data_addr(m->wall_tex[0].im,
	&(m->wall_tex[0].b_p_p), &(m->wall_tex[0].size_l), &(m->wall_tex[0].end));
	m->wall_tex[1].im = mlx_xpm_file_to_image(m->mlx, "texture/redbrick.xpm",
						&m->wall_tex[1].w, &m->wall_tex[1].h);
	m->wall_tex[1].addr = mlx_get_data_addr(m->wall_tex[1].im,
	&(m->wall_tex[1].b_p_p), &(m->wall_tex[1].size_l), &(m->wall_tex[1].end));
	m->wall_tex[2].im = mlx_xpm_file_to_image(m->mlx, "texture/eagle.xpm",
						&m->wall_tex[2].w, &m->wall_tex[2].h);
	m->wall_tex[2].addr = mlx_get_data_addr(m->wall_tex[2].im,
	&(m->wall_tex[2].b_p_p), &(m->wall_tex[2].size_l), &(m->wall_tex[2].end));
	m->wall_tex[3].im = mlx_xpm_file_to_image(m->mlx, "texture/colorstone.xpm",
						&m->wall_tex[3].w, &m->wall_tex[3].h);
	m->wall_tex[3].addr = mlx_get_data_addr(m->wall_tex[3].im,
	&(m->wall_tex[3].b_p_p), &(m->wall_tex[3].size_l), &(m->wall_tex[3].end));
	m->wall_tex[4].im = mlx_xpm_file_to_image(m->mlx, "texture/wood.xpm",
						&m->wall_tex[4].w, &m->wall_tex[4].h);
	m->wall_tex[4].addr = mlx_get_data_addr(m->wall_tex[4].im,
	&(m->wall_tex[4].b_p_p), &(m->wall_tex[4].size_l), &(m->wall_tex[4].end));
}

void		fill_data(t_mlx *m)
{
	m->px = (double)22 + 0.2;
	m->py = (double)1 + 0.2;
	m->plane_x = 0;
	m->plane_y = 0.66;
	m->dx = -1;
	m->dy = 0;
	m->move_speed = 0.1;
	m->rot_speed = 0.07;
	m->wall_tex = (t_im *)malloc(sizeof(t_im) * 5);
	create_texture(m);
}
