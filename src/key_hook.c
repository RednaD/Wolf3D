/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:52:01 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/27 18:57:50 by arusso           ###   ########.fr       */
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

int		get_pos(t_global *g, int key)
{
	if (!(UP) && !(DOWN))
		return (0);
	if (UP)
	{
		if (g->map[(int)(g->player.pos_y)][(int)(g->player.pos_x \
					+ g->player.dir_x * g->player.speed * 2)] <= 19)
			g->player.pos_x += g->player.dir_x * g->player.speed;
		if (g->map[(int)(g->player.pos_y + g->player.dir_y * g->player.speed * 2)]\
				[(int)(g->player.pos_x)] <= 19)
			g->player.pos_y += g->player.dir_y * g->player.speed;
	}
	else if (DOWN)
	{
		if (g->map[(int)(g->player.pos_y)][(int)(g->player.pos_x \
					- g->player.dir_x * g->player.speed * 2)] <= 19)
			g->player.pos_x -= g->player.dir_x * g->player.speed;
		if (g->map[(int)(g->player.pos_y - g->player.dir_y * g->player.speed * 2)]\
				[(int)(g->player.pos_x)] <= 19)
			g->player.pos_y -= g->player.dir_y * g->player.speed;
	}
	buh(g);
	return (1);
}

int		change_tex(t_global *g, int key)
{
	if (!(T))
		return (0);
	if (g->bonus_tex == 0)
		g->bonus_tex = 1;
	else
		g->bonus_tex = 0;
	buh(g);
	return (1);
}

int		close_mouse(t_global *g, int key)
{
	(void)key;
	(void)g;
	exit(1);
	return (0);
}

int		sprint(t_global *g, int key)
{
	printf("key = %d\n", key);
	if (!(SHIFT))
		return (0);
	if (g->player.speed == 0.1)
		g->player.speed = 0.2;
	else
		g->player.speed = 0.1;
	return (1);
}

int		close_map(t_global *g, int key)
{
	if (!(ESCAPE))
		return (0);
	free_parse(g->map, g->max_y);
	exit(EXIT_SUCCESS);
}

int		deal_key(int key, t_global *g)
{
	int i;

	i = 0;
	while ((i < MAX_FUNC) && !g->key_func[i](g, key))
		i++;
	return (0);
}
