/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 15:48:08 by iporsenn          #+#    #+#             */
/*   Updated: 2018/11/23 14:18:26 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

static void	init_ray(t_global *g, t_local *l, int x)
{
	l->ray.map_x = (int)g->player.pos_x;
	l->ray.map_y = (int)g->player.pos_y;
	l->cam_x = 2 * x / (long double)WIDTH - 1;
	l->ray.dir_x = g->player.dir_x + g->player.plane_x * l->cam_x;
	l->ray.dir_y = g->player.dir_y + g->player.plane_y * l->cam_x;
	l->ray.delta_x = sqrt(1 + (l->ray.dir_y * l->ray.dir_y) / \
			(l->ray.dir_x * l->ray.dir_x));
	l->ray.delta_y = sqrt(1 + (l->ray.dir_x * l->ray.dir_x) / \
			(l->ray.dir_y * l->ray.dir_y));
	l->step_x = (l->ray.dir_x < 0) ? -1 : 1;
	l->ray.side_x = (l->ray.dir_x < 0) ? \
			((g->player.pos_x - l->ray.map_x) * l->ray.delta_x) \
			: ((l->ray.map_x + 1.0 - g->player.pos_x) * l->ray.delta_x);
	l->step_y = (l->ray.dir_y < 0) ? -1 : 1;
	l->ray.side_y = (l->ray.dir_y < 0) ? \
				((g->player.pos_y - l->ray.map_y) * l->ray.delta_y) \
				: ((l->ray.map_y + 1.0 - g->player.pos_y) * l->ray.delta_y);
}

static void	loop(t_global *g, t_local *l)
{
	if (l->ray.side_x < l->ray.side_y)
	{
		l->ray.side_x += l->ray.delta_x;
		l->ray.map_x += l->step_x;
		l->side = 0;
	}
	else
	{
		l->ray.side_y += l->ray.delta_y;
		l->ray.map_y += l->step_y;
		l->side = 1;
	}
	if (g->map[l->ray.map_y][l->ray.map_x] > 19)
		l->hit = 1;
}

static void	raycast_loop(int x, int end, t_global *g)
{
	t_local	l;

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

static void	*launch_thread(void *data)
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

int			start_wolf(t_global *g)
{
	int i;

	i = -1;
	update_input(g);
	if (g->p_img)
		mlx_destroy_image(g->mlx, g->p_img);
	if (g->mini_map.p_img)
		mlx_destroy_image(g->mlx, g->mini_map.p_img);
	if (!(g->p_img = mlx_new_image(g->mlx, WIDTH, HEIGHT)))
		error("Error : mlx_new_image() failed");
	g->data = (unsigned int*)mlx_get_data_addr(g->p_img, &g->bpp, \
			&g->size, &g->endian);
	while (++i < THREAD)
		pthread_create(&g->thread[i], NULL, launch_thread, g);
	i = -1;
	while (++i < THREAD)
		pthread_join(g->thread[i], NULL);
	mlx_put_image_to_window(g->mlx, g->win, g->p_img, 0, 0);
	launch_mini_map(g);
	return (0);
}
