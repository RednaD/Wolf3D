/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:47:40 by iporsenn          #+#    #+#             */
/*   Updated: 2018/06/12 14:47:41 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

void	print_parse(t_global *global)
{
	int i;
	int j;

	i = -1;
	while (++i < global->map_y)
	{
		j = -1;
		while (++j < global->map_x)
		{
			ft_putnbr(global->map[i][j]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	printf("x_init = %Lf, y_init = %Lf\n", global->player.pos_x, \
														global->player.pos_y);
}
