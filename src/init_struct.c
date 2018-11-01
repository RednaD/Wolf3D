/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 17:53:25 by iporsenn          #+#    #+#             */
/*   Updated: 2018/11/01 16:43:36 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

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

static char	**load_map(t_global *g)
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
			error("Error : parsing failed.");
		if (ft_strlen(line) > 600 || i > 200)
			error("Error : invalid map.");
		dest[i] = ft_strdup(line);
		ft_strdel(&line);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

static void	check_tex(t_global *g)
{
	int	i;
	int	j;

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
	close(g->fd);
	g->max_x = count_word((const char*)c_map[0], ' ');
	if (!(g->map = (int**)malloc(sizeof(int*) * ft_tablen(c_map) + 1)))
		error("Error : malloc failed.");
	len_tab = ft_tablen(c_map);
	i = 0;
	while (i != len_tab)
	{
		if (!(g->map[i] = ft_splitoa(c_map[i], ' ')))
			error("Error : parsing failed.");
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
