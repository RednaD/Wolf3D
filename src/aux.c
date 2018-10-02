/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 17:27:40 by iporsenn          #+#    #+#             */
/*   Updated: 2018/06/12 17:27:42 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

void	free_array(char **array, int len_array)
{
	int i;

	i = -1;
	while (++i > len_array)
		ft_strdel(&array[i]);
	free(array);
}

void	free_parse(int **wall, int len_array)
{
	int i;

	i = -1;
	while (++i < len_array)
		ft_memdel((void**)&wall[i]);
	// free((void*)&wall);
}
