/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:27:40 by iporsenn          #+#    #+#             */
/*   Updated: 2018/11/01 15:45:24 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

static void	get_tex(t_global *g, t_local *l)
{
	if (g->bonus_tex == 1)
		get_tex_bonus(g, l);
	else
	{
		l->t_type = 1;
		if (l->side == 0 && l->ray.dir_x > 0)
			l->t_id = 0;
		else if (l->side == 0 && l->ray.dir_x <= 0)
			l->t_id = 1;
		else if (l->side == 1 && l->ray.dir_y > 0)
			l->t_id = 2;
		else
			l->t_id = 3;
	}
}

static void	draw_wall(float *start, float *end, t_global *g, t_local *l)
{
	int				y;

	l->t_type = 0;
	l->t_id = 0;
	get_tex(g, l);
	if (!(g->tex[l->t_type][l->t_id].p_img))
		error("Error : texture doesn't exists.");
	l->wall_x = (l->side == 0 ? \
			l->ray.w_dist * l->ray.dir_y + g->player.pos_y \
			: l->ray.w_dist * l->ray.dir_x + g->player.pos_x);
	l->wall_x -= floor(l->wall_x);
	l->t_x = (int)(l->wall_x * (double)(g->tex[l->t_type][l->t_id].x));
	if ((l->side == 0 && l->ray.dir_x > 0) \
			|| (l->side == 1 && l->ray.dir_y < 0))
		l->t_x = g->tex[l->t_type][l->t_id].x - l->t_x - 1;
	y = start[0] - 1;
	while (++y < end[0])
	{
		l->t_y = (((y * 256 - HEIGHT * 128 + l->line_height * 128) \
					* g->tex[l->t_type][l->t_id].y) / l->line_height) / 256;
		((int*)g->data)[(int)(start[1] + y * WIDTH)] = g->tex[l->t_type]\
			[l->t_id].data[l->t_x + (l->t_y * g->tex[l->t_type][l->t_id].x)];
	}
}

static void	loop_floor_ceiling(float *end, t_global *g, t_local *l, int y)
{
	l->cur_dist = HEIGHT / (2.0 * y - HEIGHT);
	l->cur_pos = (l->cur_dist - l->pl_dist) / (l->ray.w_dist - l->pl_dist);
	l->cur_x = l->cur_pos * l->wall_pos_x + (1.0 - l->cur_pos) * \
																g->player.pos_x;
	l->cur_y = l->cur_pos * l->wall_pos_y + (1.0 - l->cur_pos) * \
																g->player.pos_y;
	l->t_x = (int)(l->cur_x * g->tex[0][0].x) % g->tex[0][0].x;
	l->t_y = (int)(l->cur_y * g->tex[0][0].y) % g->tex[0][0].y;
	((int*)g->data)[(int)(end[1] + y * WIDTH)] = \
						g->tex[0][0].data[l->t_x + (l->t_y * g->tex[0][0].x)];
	l->t_x = (int)(l->cur_x * g->tex[2][0].x) % g->tex[2][0].x;
	l->t_y = (int)(l->cur_y * g->tex[2][0].y) % g->tex[2][0].y;
	((int*)g->data)[(int)(end[1] + (HEIGHT - y - 1) * WIDTH)] = \
						g->tex[2][0].data[l->t_x + (l->t_y * g->tex[2][0].x)];
}

static void	draw_floor_ceiling(float *end, t_global *g, t_local *l)
{
	int		y;

	l->wall_pos_x = l->ray.map_x + (l->side == 1 ? l->wall_x : 0);
	l->wall_pos_y = l->ray.map_y + (l->side == 0 ? l->wall_x : 0);
	if (l->side == 0 && l->ray.dir_x > 0)
		l->wall_pos_x = l->ray.map_x;
	else if (l->side == 0 && l->ray.dir_x < 0)
		l->wall_pos_x = l->ray.map_x + 1.0;
	else if (l->side == 1 && l->ray.dir_y > 0)
		l->wall_pos_y = l->ray.map_y;
	else
		l->wall_pos_y = l->ray.map_y + 1.0;
	l->pl_dist = 0.0;
	y = end[0] - 1;
	while (++y < HEIGHT)
		loop_floor_ceiling(end, g, l, y);
}

void		set_coord(t_global *g, t_local *l, int x)
{
	float			start[2];
	float			end[2];

	l->ray.w_dist = (l->side == 0) ? \
		(l->ray.map_x - g->player.pos_x + (1 - l->step_x) / 2) / l->ray.dir_x \
		: (l->ray.map_y - g->player.pos_y + (1 - l->step_y) / 2) / l->ray.dir_y;
	l->line_height = (int)(HEIGHT / l->ray.w_dist);
	start[0] = (float)(-l->line_height / 2 + HEIGHT / 2 - 1);
	start[0] = (start[0] < 0) ? 0 : start[0];
	end[0] = (float)(l->line_height / 2 + HEIGHT / 2);
	end[0] = (end[0] >= HEIGHT) ? HEIGHT - 1 : end[0];
	start[1] = x;
	end[1] = x;
	draw_wall(start, end, g, l);
	end[0] = (end[0] < 0 ? HEIGHT : end[0]);
	draw_floor_ceiling(end, g, l);
}
