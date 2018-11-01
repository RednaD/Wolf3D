/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   born_to_norm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 17:03:47 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/31 17:03:48 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

char	*get_path(int i, char *type)
{
	char	*path;
	char	*tmp;
	char	*tmp_2;

	path = ft_strjoin("textures/", type);
	tmp = path;
	tmp_2 = ft_itoa(i);
	path = ft_strjoin(path, tmp_2);
	free(tmp);
	free(tmp_2);
	tmp = path;
	path = ft_strjoin(path, ".xpm");
	free(tmp);
	return (path);
}

int		get_thread_id(pthread_t id, pthread_t *thread)
{
	int i;

	i = 0;
	while (i < THREAD && !pthread_equal(id, thread[i]))
		i++;
	return (i);
}

void	get_texture(t_global *g, int i, char *path, char *type)
{
	if (ft_strequ(type, "wall"))
	{
		if (!(g->tex[1][i].p_img = mlx_xpm_file_to_image(g->mlx, path, \
						&g->tex[1][i].x, &g->tex[1][i].y)))
			error("Error : no texture found for wall.");
		g->tex[1][i].data = (unsigned int*)mlx_get_data_addr(g->tex[1]\
		[i].p_img, &g->tex[1][i].bpp, &g->tex[1][i].size, &g->tex[1][i].endian);
	}
	else if (ft_strequ(type, "floor"))
	{
		if (!(g->tex[0][i].p_img = mlx_xpm_file_to_image(g->mlx, path, \
						&g->tex[0][i].x, &g->tex[0][i].y)))
			error("Error : no texture found for floor.");
		g->tex[0][i].data = (unsigned int*)mlx_get_data_addr(g->tex[0]\
		[i].p_img, &g->tex[0][i].bpp, &g->tex[0][i].size, &g->tex[0][i].endian);
	}
	else
	{
		if (!(g->tex[2][i].p_img = mlx_xpm_file_to_image(g->mlx, path, \
						&g->tex[2][i].x, &g->tex[2][i].y)))
			error("Error : no texture found for ceiling.");
		g->tex[2][i].data = (unsigned int*)mlx_get_data_addr(g->tex[2]\
		[i].p_img, &g->tex[2][i].bpp, &g->tex[2][i].size, &g->tex[2][i].endian);
	}
}

void	get_tex_bonus(t_global *g, t_local *l)
{
	if (g->map[l->ray.map_y][l->ray.map_x] >= 10 && \
			g->map[l->ray.map_y][l->ray.map_x] < 20)
	{
		l->t_type = 0;
		l->t_id = g->map[l->ray.map_y][l->ray.map_x] - 10;
	}
	else if (g->map[l->ray.map_y][l->ray.map_x] >= 20 && \
			g->map[l->ray.map_y][l->ray.map_x] < 30)
	{
		l->t_type = 1;
		l->t_id = g->map[l->ray.map_y][l->ray.map_x] - 20;
	}
	else if (g->map[l->ray.map_y][l->ray.map_x] >= 30 && \
			g->map[l->ray.map_y][l->ray.map_x] < 40)
	{
		l->t_type = 2;
		l->t_id = g->map[l->ray.map_y][l->ray.map_x] - 30;
	}
}

void	free_tmp(int **tmp, int i)
{
	while (--i > -1)
		free(tmp[i]);
	free(tmp);
}
