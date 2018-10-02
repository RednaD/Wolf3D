/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:26:24 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/02 16:33:51 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

int		main(int ac, char **av)
{
	t_global	*global;

	if (ac != 2)
		error("Error : please enter a map file name.\n./wolf3d map_file.txt");
	if (!(global = (t_global*)malloc(sizeof(t_global))))
		error("Error : malloc failed.");
	global->name = av[1];
	if (!(check_map(global)))
		error("Error : unvalid map file or map file doesn't exist.");
	init_map(global);
	init_global(global);
	// launch_mini_map(&global);
	// raycast_loop(&global);
	mlx_put_image_to_window(global->mlx, global->win, \
			global->floor.p_img, global->floor.x, global->floor.y);
	mlx_hook(global->win, 2, (1L << 0), deal_key, &global);
	mlx_loop(global->mlx);
	return (0);
}
