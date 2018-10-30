/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 17:53:25 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/30 14:53:25 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

static void	get_texture(t_global *g, int i, char *path, char *type)
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

static void	init_textures(t_global *g)
{
	char	*path;
	int		i;

	i = -1;
	while (++i < NB_WALL)
	{
		path = get_path(i, "wall");
		get_texture(g, i, path, "wall");
		ft_strdel(&path);
	}
	i = -1;
	while (++i < NB_FLOOR)
	{
		path = get_path(i, "floor");
		get_texture(g, i, path, "floor");
		ft_strdel(&path);
	}
	i = -1;
	while (++i < NB_CEILING)
	{
		path = get_path(i, "ceiling");
		get_texture(g, i, path, "ceiling");
		ft_strdel(&path);
	}
}

void		init_global(t_global *g)
{
	int		i;

	i = -1;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, g->name);
	g->bonus_tex = 0;
	while (++i < THREAD)
		g->thread[i] = 0;
	init_textures(g);
}

char		**load_map(t_global *g)
{
	char	**dest;
	char	*line;
	int		ret;
	int		i;

	line = NULL;
	if ((ret = get_next_line(g->fd, &line)) < 0)
		error("Error : map file invalid.");
	ft_strdel(&line);
	i = 0;
	if (!(dest = (char**)malloc(sizeof(char*) * g->max_y + 1)))
		error("Error : malloc failed.");
	while ((ret = get_next_line(g->fd, &line)))
	{
		if (ret == -1)
			error("Nope.");
		dest[i] = ft_strdup(line);
		ft_strdel(&line);
		i++;
	}
	dest[i] = NULL;
	close(g->fd);
	return (dest);
}

void		check_tex(t_global *g)
{
	int        i;
	int        j;

	j = -1;
	while (++j < g->max_y)
	{
		i = -1;
		while (++i < g->max_x)
		{
			if ((g->map[j][i] > 10 + NB_FLOOR - 1 && g->map[j][i] < 20)\
					|| (g->map[j][i] > 20 + NB_WALL - 1))
				error("Error : texture doesn't exist.");
		}
	}
}

void		init_map(t_global *g)
{
	char	**c_map;
	size_t	i;
	size_t	len_tab;

	c_map = load_map(g);
	g->max_x = count_word((const char*)c_map[0], ' ');
	if (!(g->map = (int**)malloc(sizeof(int*) * ft_tablen(c_map) + 1)))
		error("0");
	len_tab = ft_tablen(c_map);
	i = 0;
	while (i != len_tab)
	{
		if (!(g->map[i] = ft_splitoa(c_map[i], ' ')))
			error("0");
		i++;
	}
	g->map[i] = NULL;
	i = -1;
	while (c_map[++i])
		free(c_map[i]);
	free(c_map);
	check_start_pos(g);
	check_tex(g);
}
