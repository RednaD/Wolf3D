/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:52:01 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/27 15:46:11 by iporsenn         ###   ########.fr       */
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

static int move_right(t_global *g)
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
				+ g->player.dir_x * g->player.speed * 2)] <= 19)
		g->player.pos_x += g->player.dir_x * g->player.speed;
	if (g->map[(int)(g->player.pos_y + g->player.dir_y * g->player.speed * 2)]\
			[(int)(g->player.pos_x)] <= 19)
		g->player.pos_y += g->player.dir_y * g->player.speed;
	return (1);
}

static int move_down(t_global *g)
{
	if (g->map[(int)(g->player.pos_y)][(int)(g->player.pos_x \
				- g->player.dir_x * g->player.speed * 2)] <= 19)
		g->player.pos_x -= g->player.dir_x * g->player.speed;
	if (g->map[(int)(g->player.pos_y - g->player.dir_y * g->player.speed * 2)]\
			[(int)(g->player.pos_x)] <= 19)
		g->player.pos_y -= g->player.dir_y * g->player.speed;
	return (1);
}

void	update_input(t_global *g)
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

int		deal_key_release(int key, t_global *g)
{
	if (UP)
		g->input.up = 0;
	if (DOWN)
		g->input.down = 0;
	if (LEFT)
		g->input.left = 0;
	if (RIGHT)
		g->input.right = 0;
	return (0);
}

int		deal_key(int key, t_global *g)
{
	if (ESCAPE)
	{
		system("killall afplay");
		exit(EXIT_SUCCESS);
	}
	if (UP)
		g->input.up = 1;
	if (DOWN)
		g->input.down = 1;
	if (LEFT)
		g->input.left = 1;
	if (RIGHT)
		g->input.right = 1;
	if (SHIFT)
		g->player.speed = (g->player.speed == 0.05) ? 0.2 : 0.05;
	if (T)
		g->bonus_tex = (g->bonus_tex == 0) ? 1 : 0;
	return (0);
}
