/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 15:48:08 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/17 18:00:34 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

static int	get_color(int id)
{
	if (id == 2)
		return (0x00990099);
	if (id == 3)
		return (0x00009900);
	return (0x00FFFFFF);
}

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
	l->cam_x = 2 * x / (long double)WIDTH - 1;
	g->ray.dir_x = g->player.dir_x + g->player.plane_x * l->cam_x;
	g->ray.dir_y = g->player.dir_y + g->player.plane_y * l->cam_x;
	g->ray.map_x = (int)g->player.pos_x;
	g->ray.map_y = (int)g->player.pos_y;
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
	if (g->map[g->ray.map_y][g->ray.map_x] > 1)
		l->hit = 1;
}

static void	set_coord(t_global *g, t_local *l, int x)
{
	int			line_height;
	float		coord_src[2];
	float		coord_dest[2];

	g->ray.perp_walldist = (l->side == 0) ? \
		(g->ray.map_x - g->player.pos_x + (1 - l->step_x) / 2) / g->ray.dir_x \
	: (g->ray.map_y - g->player.pos_y + (1 - l->step_y) / 2) / g->ray.dir_y;
	line_height = (int)(HEIGHT / g->ray.perp_walldist);
	coord_src[0] = (float)(-line_height / 2 + HEIGHT / 2);
	coord_src[0] = (coord_src[0] < 0) ? 0 : coord_src[0];
	coord_dest[0] = (float)(line_height / 2 + HEIGHT / 2);
	coord_dest[0] = (coord_dest[0] >= HEIGHT) ? HEIGHT - 1 : coord_dest[0];
	coord_src[1] = x;
	coord_dest[1] = x;
	//draw_h(coord_src, coord_dest, g);
	g->color = get_color(g->map[g->ray.map_y][g->ray.map_x]);
	draw_segment(coord_src, coord_dest, g);
}

void	raycast_loop(int x, int end, t_global *g)
{
	t_local		l;

	while (x < WIDTH && x < end)
	{
		init_ray(g, &l, x);
		l.hit = 0;
		while (l.hit == 0)
			loop(g, &l);
		set_coord(g, &l, x);
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
	return (NULL);
}

void	buh(t_global *g)
{
	int i;

	i = -1;
	if (g->p_img)
		mlx_destroy_image(g->mlx, g->p_img);
	g->p_img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->img_addr = mlx_get_data_addr(g->p_img, &g->bpp, \
			&g->size, &g->endian);
	while (++i < THREAD)
		pthread_create(&g->thread[i], NULL, launch_thread, g);
	i = -1;
	while (++i < THREAD)
		pthread_join(g->thread[i], NULL);
	mlx_put_image_to_window(g->mlx, g->win, g->p_img, 0, 0);
}
