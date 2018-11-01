/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 17:19:16 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/30 17:19:18 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

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
		g->player.speed = (g->player.speed == 0.04) ? 0.08 : 0.04;
	if (T)
		g->bonus_tex = (g->bonus_tex == 0) ? 1 : 0;
	return (0);
}
