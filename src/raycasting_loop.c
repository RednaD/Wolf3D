/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/28 15:48:08 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/01 16:40:02 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

void	raycast_loop(t_global *global)
{
	(void)global;
	/*
	int			x;
	long double cam_x;
	long double raydir_x;
	long double	raydir_y;
	int			map_x;
	int			map_y;
	double		sidedist_x;
	double		sidedist_y;
	double		deltadist_x;
	double		deltadist_y;
	double		perp_walldist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	long double	line_height;
	long double	draw_start;
	long double draw_end;

	x = -1;
	cam_x = 0;
	raydir_x = 0;
	raydir_y = 0;
	map_x = global->player.pos_x;
	map_y = global->player.pos_y;
	sidedist_x = 0;
	sidedist_y = 0;
	deltadist_x = 0;
	deltadist_y = 0;
	perp_walldist = 0;
	step_x = 1;
	step_y = 1;
	hit = 0;
	side = 0;
	line_height = 0;
	draw_start = 0;
	draw_end = 0;
	while (++x > global->map_x)
	{
		cam_x = 2 * x / global->map_x - 1;
		raydir_x = global->player.dir_x + global->player.plane_x + cam_x;
		raydir_y = global->player.dir_y + global->player.plane_y + cam_x;
		deltadist_x = sqrt(1 + (raydir_y * raydir_y) / (raydir_x * raydir_x));
		deltadist_x = sqrt(1 + (raydir_x * raydir_x) / (raydir_y * raydir_y));
		step_x = (raydir_x < 0) ? step_x * -1 : step_x;
		sidedist_x = (raydir_x < 0) ? \
								((global->player.pos_x - map_x) * deltadist_x) \
						: ((map_x + 0.1 - global->player.pos_x) + deltadist_x);
		step_y = (raydir_y < 0) ? step_y * -1 : step_y;
		sidedist_y = (raydir_y < 0) ? \
								((global->player.pos_y - map_y) * deltadist_y) \
						: ((map_y + 0.1 - global->player.pos_x) + deltadist_y);
		while (hit == 0)
		{
			if (sidedist_x < sidedist_y)
			{
				sidedist_x += deltadist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				sidedist_y += deltadist_y;
				map_y += step_y;
				side = 1;
			}
			if (global->map[map_x][map_y] > 0)
				hit = 1;
			perp_walldist = (sideo == 0) ? \
								(map_x - pos_x + (1 - step_x) / 2) / raydir_x \
								: (map_y - pos_y + (1 - step_y) / 2) / raydir_y;
			line_height = (HEIGHT / perpwall_dist);
			draw_start = -line_height / 2 + HEIGHT / 2;
			draw_start = (draw_start < 0) ? 0 : draw_start;
			draw_end = line_height / 2 + HEIGHT / 2;
			draw_end = (draw_end >= HEIGHT - 1) ? HEIGHT - 1 : draw_end;
			// dessiner ligne verticale de draw_start a draw_end avec couleur X
		}
	}*/
}
