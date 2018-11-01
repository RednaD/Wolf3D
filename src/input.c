/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:04:04 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/31 17:04:06 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

static int	move_left(t_global *g)
{
	long double tmp_dir;
	long double tmp_plane;

	tmp_dir = g->player.dir_x;
	tmp_plane = g->player.plane_x;
	g->player.dir_x = g->player.dir_x * \
					cos(-g->player.rot) - g->player.dir_y * sin(-g->player.rot);
	g->player.dir_y = tmp_dir * sin(-g->player.rot) + g->player.dir_y * \
															cos(-g->player.rot);
	g->player.plane_x = g->player.plane_x * \
				cos(-g->player.rot) - g->player.plane_y * sin(-g->player.rot);
	g->player.plane_y = tmp_plane * sin(-g->player.rot) \
									+ g->player.plane_y * cos(-g->player.rot);
	return (1);
}

static int	move_right(t_global *g)
{
	long double tmp_dir;
	long double tmp_plane;

	tmp_dir = g->player.dir_x;
	tmp_plane = g->player.plane_x;
	g->player.dir_x = g->player.dir_x * cos(g->player.rot) - \
					g->player.dir_y * sin(g->player.rot);
	g->player.dir_y = tmp_dir * sin(g->player.rot) + g->player.dir_y * \
		cos(g->player.rot);
	g->player.plane_x = g->player.plane_x * cos(g->player.rot) - \
				g->player.plane_y * sin(g->player.rot);
	g->player.plane_y = tmp_plane * sin(g->player.rot) + \
	g->player.plane_y * cos(g->player.rot);
	return (1);
}

static int	move_up(t_global *g)
{
	if (g->map[(int)(g->player.pos_y)][(int)(g->player.pos_x \
			+ g->player.dir_x * 0.25)] <= 19 &&
			g->map[(int)(g->player.pos_y)][(int)(g->player.pos_x \
			+ g->player.dir_x * 0.25)] > 9)
		g->player.pos_x += g->player.dir_x * g->player.speed;
	if ((g->map[(int)(g->player.pos_y + g->player.dir_y * 0.25)]\
			[(int)(g->player.pos_x)] <= 19) && (g->map[(int)(g->player.pos_y +\
			g->player.dir_y * 0.25)]\
			[(int)(g->player.pos_x)] > 9))
		g->player.pos_y += g->player.dir_y * g->player.speed;
	return (1);
}

static int	move_down(t_global *g)
{
	if (g->map[(int)(g->player.pos_y)][(int)(g->player.pos_x - \
					g->player.dir_x * 0.25)] <= 19 && \
					g->map[(int)(g->player.pos_y)][(int)(g->player.pos_x - \
					g->player.dir_x * 0.25)] > 9)
		g->player.pos_x -= g->player.dir_x * g->player.speed;
	if (g->map[(int)(g->player.pos_y - g->player.dir_y * 0.25)]\
					[(int)(g->player.pos_x)] <= 19 && \
					g->map[(int)(g->player.pos_y -\
					g->player.dir_y * 0.25)][(int)(g->player.pos_x)] > 9)
		g->player.pos_y -= g->player.dir_y * g->player.speed;
	return (1);
}

void		update_input(t_global *g)
{
	if (g->input.up)
		move_up(g);
	if (g->input.down)
		move_down(g);
	if (g->input.right)
		move_right(g);
	if (g->input.left)
		move_left(g);
}
