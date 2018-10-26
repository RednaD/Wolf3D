/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 15:48:08 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/26 18:29:19 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

static int		get_thread_id(pthread_t id, pthread_t *thread)
{
	int i;

	i = 0;
	while (i < THREAD && !pthread_equal(id, thread[i]))
		i++;
	return (i);
}

static void	init_ray(t_global *g, t_local *l, int x)
{
	g->ray.map_x = (int)g->player.pos_x;
	g->ray.map_y = (int)g->player.pos_y;
	l->cam_x = 2 * x / (long double)WIDTH - 1;
	g->ray.dir_x = g->player.dir_x + g->player.plane_x * l->cam_x;
	g->ray.dir_y = g->player.dir_y + g->player.plane_y * l->cam_x;
	g->ray.deltadist_x = sqrt(1 + (g->ray.dir_y * g->ray.dir_y) / \
			(g->ray.dir_x * g->ray.dir_x));
	g->ray.deltadist_y = sqrt(1 + (g->ray.dir_x * g->ray.dir_x) / \
			(g->ray.dir_y * g->ray.dir_y));
	l->step_x = (g->ray.dir_x < 0) ? -1 : 1;
	g->ray.sidedist_x = (g->ray.dir_x < 0) ? \
			((g->player.pos_x - g->ray.map_x) * g->ray.deltadist_x) \
			: ((g->ray.map_x + 1.0 - g->player.pos_x) * g->ray.deltadist_x);
	l->step_y = (g->ray.dir_y < 0) ? -1 : 1;
	g->ray.sidedist_y = (g->ray.dir_y < 0) ? \
				((g->player.pos_y - g->ray.map_y) * g->ray.deltadist_y) \
				: ((g->ray.map_y + 1.0 - g->player.pos_y) * g->ray.deltadist_y);
}

static void	loop(t_global *g, t_local *l)
{
	if (g->ray.sidedist_x < g->ray.sidedist_y)
	{
		g->ray.sidedist_x += g->ray.deltadist_x;
		g->ray.map_x += l->step_x;
		l->side = 0;
	}
	else
	{
		g->ray.sidedist_y += g->ray.deltadist_y;
		g->ray.map_y += l->step_y;
		l->side = 1;
	}
	if (g->map[g->ray.map_y][g->ray.map_x] > 19)
		l->hit = 1;
}

void		get_tex_bonus(t_global *g, t_local *l)
{
	if (g->map[g->ray.map_y][g->ray.map_x] >= 10 && \
			g->map[g->ray.map_y][g->ray.map_x] < 20)
	{
		l->t_type = 0;
		l->t_id = g->map[g->ray.map_y][g->ray.map_x] - 10;
	}
	else if (g->map[g->ray.map_y][g->ray.map_x] >= 20 && \
			g->map[g->ray.map_y][g->ray.map_x] < 30)
	{
		l->t_type = 1;
		l->t_id = g->map[g->ray.map_y][g->ray.map_x] - 20;
	}
	else if (g->map[g->ray.map_y][g->ray.map_x] >= 30 && \
			g->map[g->ray.map_y][g->ray.map_x] < 40)
	{
		l->t_type = 2;
		l->t_id = g->map[g->ray.map_y][g->ray.map_x] - 30;
	}
}

void		get_tex(t_global *g, t_local *l)
{
	if (g->bonus_tex == 1)
		get_tex_bonus(g, l);
	else
	{
		l->t_type = 1;
		if (l->side == 0 && g->ray.dir_x > 0)
			l->t_id = 0;
		else if (l->side == 0 && g->ray.dir_x <= 0)
			l->t_id = 1;
		else if (l->side == 1 && g->ray.dir_y > 0)
			l->t_id = 2;
		else
			l->t_id = 3;
	}
}

static void	draw_wall(float *start, float *end, t_global *g, t_local *l)
{
	int	y;

	l->t_type = 0;
	l->t_id = 0;
	get_tex(g, l);
	if (!(g->tex[l->t_type][l->t_id].p_img))
		error("Error : texture doesn't exists.");
	l->wall_x = (l->side == 0 ? \
			g->ray.w_dist * g->ray.dir_y + g->player.pos_y \
			: g->ray.w_dist * g->ray.dir_x + g->player.pos_x);
	l->wall_x -= floor(l->wall_x);
	l->t_x = (int)(l->wall_x * (double)(g->tex[l->t_type][l->t_id].x));
	if ((l->side == 0 && g->ray.dir_x > 0) \
			|| (l->side == 1 && g->ray.dir_y < 0))
		l->t_x = g->tex[l->t_type][l->t_id].x - l->t_x - 1;
	y = start[0] - 1;
	while (++y < end[0])
	{
		l->t_y = (((y * 256 - HEIGHT * 128 + l->line_height * 128) \
					* g->tex[l->t_type][l->t_id].y) / l->line_height) / 256;
		((int*)g->data)[(int)(start[1] + y * WIDTH)] = \
			g->tex[l->t_type][l->t_id].data[l->t_x + (l->t_y * g->tex[l->t_type][l->t_id].x)];
	}
}

static void	draw_floor_ceiling(float *start, float *end, t_global *g, \
		t_local *l)
{
	int		y;

	l->wall_pos_x = g->ray.map_x + (l->side == 1 ? l->wall_x : 0);
	//l->wall_pos_x += (l->side == 0 ? 0 : 1.0);
	l->wall_pos_y = g->ray.map_y + (l->side == 0 ? l->wall_x : 0);
	//l->wall_pos_y += (l->side == 1  ? 0 : 1.0);
	l->pl_dist = 0.0;
	y = end[0];
	while (++y < HEIGHT)
	{
		l->cur_dist = HEIGHT / (2.0 * y - HEIGHT);
		l->cur_pos = (l->cur_dist - l->pl_dist) / (g->ray.w_dist - l->pl_dist);
		l->cur_x = l->cur_pos * l->wall_pos_x + \
				   (1.0 - l->cur_pos) * g->player.pos_x;
		l->cur_y = l->cur_pos * l->wall_pos_y + \
				   (1.0 - l->cur_pos) * g->player.pos_y;
		//l->t_x = (int)(l->cur_x * g->tex[0][0].x) % g->tex[0][0].x;
		//l->t_y = (int)(l->cur_y * g->tex[0][0].y) % g->tex[0][0].y;
		l->t_x = (int)(l->cur_x * g->tex[0][0].x) % g->tex[0][0].x;
		l->t_y = (int)(l->cur_y * g->tex[0][0].y) % g->tex[0][0].y;
		((int*)g->data)[(int)(start[1] + y * WIDTH)] \
			= g->tex[0][0].data[l->t_x + (l->t_y * g->tex[0][0].x)];
		((int*)g->data)[(int)(start[1] + (HEIGHT - y) * WIDTH)] \
			= g->tex[2][0].data[l->t_x + (l->t_y * g->tex[2][0].x)];
	}
}

static void	set_coord(t_global *g, t_local *l, int x)
{
	float		start[2];
	float		end[2];

	g->ray.w_dist = (l->side == 0) ? \
		(g->ray.map_x - g->player.pos_x + (1 - l->step_x) / 2) / g->ray.dir_x \
		: (g->ray.map_y - g->player.pos_y + (1 - l->step_y) / 2) / g->ray.dir_y;
	l->line_height = (int)(HEIGHT / g->ray.w_dist);
	start[0] = (float)(-l->line_height / 2 + HEIGHT / 2);
	start[0] = (start[0] < 0) ? 0 : start[0];
	end[0] = (float)(l->line_height / 2 + HEIGHT / 2);
	end[0] = (end[0] >= HEIGHT) ? HEIGHT - 1 : end[0];
	start[1] = x;
	end[1] = x;
	draw_wall(start, end, g, l);
	end[0] = (end[0] < 0 ? HEIGHT : end[0]);
	draw_floor_ceiling(start, end, g, l);
}

void	raycast_loop(int x, int end, t_global *g)
{
	t_local		*l;

	l = (t_local*)malloc(sizeof(t_local));
	while (x < WIDTH && x < end)
	{
		init_ray(g, l, x);
		l->hit = 0;
		while (l->hit == 0)
			loop(g, l);
		set_coord(g, l, x);
		x++;
	}
}

static void		*launch_thread(void *data)
{
	int			start;
	int			end;
	int			padding;
	t_global	*g;

	g = (t_global *)data;
	padding = WIDTH / THREAD;
	start = get_thread_id(pthread_self(), g->thread) * padding;
	end = start + padding + 1;
	raycast_loop(start, end, g);
	pthread_exit(NULL);
}

void	buh(t_global *g)
{
	int i;

	i = -1;
	if (g->p_img)
		mlx_destroy_image(g->mlx, g->p_img);
	g->p_img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->data = (unsigned int*)mlx_get_data_addr(g->p_img, &g->bpp, \
			&g->size, &g->endian);
	while (++i < THREAD)
		pthread_create(&g->thread[i], NULL, launch_thread, g);
	i = -1;
	while (++i < THREAD)
		pthread_join(g->thread[i], NULL);
	mlx_put_image_to_window(g->mlx, g->win, g->p_img, 0, 0);
}
