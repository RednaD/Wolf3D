/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_square.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:19:39 by iporsenn          #+#    #+#             */
/*   Updated: 2018/06/19 17:19:41 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

void	draw_white_square(int x, int y, t_global *global)
{
	int i;
	int len_x;
	int	len_y;

	len_x = x + SQUARE;
	len_y = y + SQUARE;
	while (x < WIDTH && x <= len_x)
	{
		i = y;
		while (++i <= HEIGHT && i <= len_y)
			mlx_pixel_put_to_image(global, x, i, 0xFFFFFF);
		x++;
	}
}

void	draw_black_square(int x, int y, t_global *global)
{
	int i;
	int len;

	len = x + SQUARE;
	while (x < WIDTH && x < len)
	{
		i = y;
		while (++i < HEIGHT && i <= y + SQUARE)
			mlx_pixel_put_to_image(global, x, i, 0x000000);
		x++;
	}
}
