/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:52:01 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/17 18:40:46 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/wolf_3d.h"

int		get_dir(t_global *g, int key)
{
	long double tmp_dir;
	long double tmp_plane;

	if (!(LEFT) && !(RIGHT))
		return (0);
	tmp_dir = g->player.dir_x;
	tmp_plane = g->player.plane_x;
	g->player.dir_x = RIGHT ? g->player.dir_x * cos(g->player.rot)\
					  - g->player.dir_y * sin(g->player.rot) \
					  : g->player.dir_x * cos(-g->player.rot) \
					  - g->player.dir_y * sin(-g->player.rot);
	g->player.dir_y = RIGHT ? tmp_dir * sin(g->player.rot) \
					  + g->player.dir_y * cos(g->player.rot) \
					  : tmp_dir * sin(-g->player.rot) \
					  + g->player.dir_y * cos(-g->player.rot);
	g->player.plane_x = RIGHT ? g->player.plane_x * cos(g->player.rot) \
						- g->player.plane_y * sin(g->player.rot) \
						: g->player.plane_x * cos(-g->player.rot) \
						- g->player.plane_y * sin(-g->player.rot);
	g->player.plane_y = RIGHT ? tmp_plane * sin(g->player.rot) \
						+ g->player.plane_y * cos(g->player.rot) \
						: tmp_plane * sin(-g->player.rot) \
						+ g->player.plane_y * cos(-g->player.rot);
	buh(g);
	return (1);
}

int		sprint(t_global *g, int key)
{
	if (!(SHIFT))
		return (0);
	if (g->player.speed == 0.1)
		g->player.speed = 0.3;
	else
		g->player.speed = 0.1;
	return (1);
}

int		get_pos(t_global *g, int key)
{
	if (!(UP) && !(DOWN))
		return (0);
	if (UP)
	{
		printf("pos_x = %Lf, pos_y = %Lf\nvalue = %d\n\n", g->player.pos_x, \
				g->player.pos_y, g->map[(int)(floor(g->player.pos_y))]\
				[(int)(floor(g->player.pos_x))]);
		if (g->map[(int)(floor(g->player.pos_y + g->player.dir_y \
				* g->player.speed))][(int)(g->player.pos_x)] == 1)
				g->player.pos_x += g->player.dir_x * g->player.speed;
		if (g->map[(int)(g->player.pos_y)][(int)(floor(g->player.pos_x \
				+ g->player.dir_x * g->player.speed))] == 1)
			 g->player.pos_y += g->player.dir_y * g->player.speed;
	}
	else
	{
		if (g->map[(int)(g->player.pos_y - g->player.dir_y \
				* g->player.speed)][(int)(g->player.pos_x)] == 1)
			g->player.pos_x -= g->player.dir_x * g->player.speed;
	if (g->map[(int)(g->player.pos_y)][(int)(g->player.pos_x \
				- g->player.dir_x * g->player.speed)] == 1)
		g->player.pos_y -= g->player.dir_y * g->player.speed;
	}
	buh(g);
	return (1);
}

int		close_map(t_global *g, int key)
{
	if (ESCAPE)
		return (0);
	free_parse(g->map, g->max_y);
	exit(EXIT_SUCCESS);
}

int		deal_key(int key, t_global *g)
{
	int i;

	i = 0;
	while ((i < g->len_key) && !g->key_func[i](g, key))
		i++;
	return (0);
}
