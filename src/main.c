/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:26:24 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/30 13:14:51 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

static int	close_mouse(int key, t_global *g)
{
	(void)key;
	(void)g;
	system("killall afplay");
	exit(1);
	return (0);
}

int			main(int ac, char **av)
{
	t_global	*g;

	if (ac != 2)
		error("Error : please enter a map file name.\n./wolf3d map_file.txt");
	if (!(g = (t_global*)malloc(sizeof(t_global))))
		error("Error : malloc failed.");
	g->name = av[1];
	if (!(check_map(g)))
		error("Error : unvalid map file or map file doesn't exist.");
	init_global(g);
	init_map(g);
	//system("afplay ./sounds/hush.mp3 &");
	mlx_hook(g->win, 2, (1L << 0), deal_key, g);
	mlx_hook(g->win, 3, (1L << 1), deal_key_release, g);
	mlx_hook(g->win, 17, 1, close_mouse, g);
	mlx_loop_hook(g->mlx, &start_wolf, g);
	mlx_loop(g->mlx);
	return (0);
}
