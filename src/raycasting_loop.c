/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 15:48:08 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/25 17:33:33 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"
/*
static int	get_color(int id)
   {
   if (id == 2)
   return (0x00990099);
   if (id == 3)
   return (0x00009900);
   return (0x00FFFFFF);
   }
   */

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

void		get_tex_bonus(t_global *g, int *tex_type, int *tex_id)
{
	if (g->map[g->ray.map_y][g->ray.map_x] >= 10 && \
			g->map[g->ray.map_y][g->ray.map_x] < 20)
	{
		*tex_type = 0;
		*tex_id = g->map[g->ray.map_y][g->ray.map_x] - 10;
	}
	else if (g->map[g->ray.map_y][g->ray.map_x] >= 20 && \
			g->map[g->ray.map_y][g->ray.map_x] < 30)
	{
		*tex_type = 1;
		*tex_id = g->map[g->ray.map_y][g->ray.map_x] - 20;
	}
	else if (g->map[g->ray.map_y][g->ray.map_x] >= 30 && \
			g->map[g->ray.map_y][g->ray.map_x] < 40)
	{
		*tex_type = 2;
		*tex_id = g->map[g->ray.map_y][g->ray.map_x] - 30;
	}
}

void		get_tex(t_global *g, int *tex_type, int *tex_id, t_local *l)
{
	if (g->bonus_tex == 1)
		get_tex_bonus(g, tex_type, tex_id);
	else
	{
		*tex_type = 1;
		if (l->side == 0 && g->ray.dir_x > 0)
			*tex_id = 0;
		else if (l->side == 0 && g->ray.dir_x <= 0)
			*tex_id = 1;
		else if (l->side == 1 && g->ray.dir_y > 0)
			*tex_id = 2;
		else
			*tex_id = 3;
	}
}

static void	draw_h(float *coord_src, float *coord_dest, t_global *g, t_local *l)
{
	int	y;
	int	tex_type;
	int	tex_id;
	int tex_x;
	int tex_y;

	tex_type = 0;
	tex_id = 0;
	get_tex(g, &tex_type, &tex_id, l);
	if (!(g->tex[tex_type][tex_id].p_img))
		error("Error : texture doesn't exists.");
	l->wall_x = (l->side == 0 ? \
		g->ray.perp_walldist * g->ray.dir_y + g->player.pos_y \
		: g->ray.perp_walldist * g->ray.dir_x + g->player.pos_x);
	l->wall_x -= floor(l->wall_x);
	tex_x = (int)(l->wall_x * (double)(g->tex[tex_type][tex_id].x));
	if ((l->side == 0 && g->ray.dir_x > 0) \
			|| (l->side == 1 && g->ray.dir_y < 0))
		tex_x = g->tex[tex_type][tex_id].x - tex_x - 1;
	y = coord_src[0] - 1;
	while (++y < coord_dest[0])
	{
		tex_y = (((y * 256 - HEIGHT * 128 + l->line_height * 128) \
				* g->tex[tex_type][tex_id].y) / l->line_height) / 256;
		((int*)g->img_addr)[(int)(coord_src[1] + y * WIDTH)] \
			= g->tex[tex_type][tex_id].img_addr[tex_x \
			+ (tex_y * g->tex[tex_type][tex_id].x)];
	}
}

static void	set_coord(t_global *g, t_local *l, int x)
{
	float		coord_src[2];
	float		coord_dest[2];

	g->ray.perp_walldist = (l->side == 0) ? \
						   (g->ray.map_x - g->player.pos_x + (1 - l->step_x) / 2) / g->ray.dir_x \
						   : (g->ray.map_y - g->player.pos_y + (1 - l->step_y) / 2) / g->ray.dir_y;
	l->line_height = (g->ray.perp_walldist > 0) ? \
					 (int)(HEIGHT / g->ray.perp_walldist) : HEIGHT;
	coord_src[0] = (float)(-l->line_height / 2 + HEIGHT / 2);
	coord_src[0] = (coord_src[0] < 0) ? 0 : coord_src[0];
	coord_dest[0] = (float)(l->line_height / 2 + HEIGHT / 2);
	coord_dest[0] = (coord_dest[0] >= HEIGHT) ? HEIGHT - 1 : coord_dest[0];
	coord_src[1] = x;
	coord_dest[1] = x;
	draw_h(coord_src, coord_dest, g, l);
	//g->color = get_color(g->map[g->ray.map_y][g->ray.map_x]);
	//draw_segment(coord_src, coord_dest, g);
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
	return (NULL);
}

void	buh(t_global *g)
{
	int i;

	i = -1;
	if (g->p_img)
		mlx_destroy_image(g->mlx, g->p_img);
	g->p_img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->img_addr = (unsigned int*)mlx_get_data_addr(g->p_img, &g->bpp, \
			&g->size, &g->endian);
	while (++i < THREAD)
		pthread_create(&g->thread[i], NULL, launch_thread, g);
	i = -1;
	printf("Bu !\n");
	while (++i < THREAD)
		pthread_join(g->thread[i], NULL);
	mlx_put_image_to_window(g->mlx, g->win, g->p_img, 0, 0);
	mlx_put_image_to_window(g->mlx, g->win, g->tex[1][2].p_img, 0, 0);
}
