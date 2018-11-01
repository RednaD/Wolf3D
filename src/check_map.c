/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 17:44:07 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/30 14:38:01 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

static int	check_borders(int **map, t_global *g, int cur_x, int cur_y)
{
	if (cur_x >= g->max_x || cur_x < 0 || cur_y >= g->max_y || cur_y < 0 \
													|| map[cur_y][cur_x] < 10)
		return (1);
	if (map[cur_y][cur_x] > 19)
		return (0);
	map[cur_y][cur_x] = 99;
	return (check_borders(map, g, cur_x, cur_y - 1)
			|| check_borders(map, g, cur_x - 1, cur_y)
			|| check_borders(map, g, cur_x, cur_y + 1)
			|| check_borders(map, g, cur_x + 1, cur_y));
}

void		check_start_pos(t_global *g)
{
	t_point		start;
	int			**tmp;
	int			i;
	int			j;

	start.x = (int)g->player.pos_x;
	start.y = (int)g->player.pos_y;
	if (start.x >= g->max_x || start.y >= g->max_y || start.x < 1 \
		|| start.y < 1 || g->map[start.y][start.x] < 10
		|| g->map[start.y][start.x] > 19)
		error("Error : player can't spawn.");
	if (!(tmp = (int**)malloc(sizeof(int*) * (g->max_y))))
		error("Error : malloc failed.");
	j = -1;
	while (++j < g->max_y)
	{
		if (!(tmp[j] = (int*)malloc(sizeof(int) * (g->max_x))))
			error("Error : malloc failed.");
		i = -1;
		while (++i < g->max_x)
			tmp[j][i] = g->map[j][i];
	}
	if (check_borders(tmp, g, start.x, start.y))
		error("Error : invalid map.");
	free_tmp(tmp, g->max_y);
}

static void	init_player(t_global *g, char *line)
{
	int	coord[2];

	if (!line)
		error("Error : empty map.");
	if (count_word(line, ' ') != 2)
		error("Error : starting position not found or in a wall.");
	coord[0] = ft_atoi(line);
	coord[1] = ft_atoi(ft_strchr(line, ' '));
	g->player.pos_x = coord[0] + 0.5;
	g->player.pos_y = coord[1] + 0.5;
	g->player.dir_x = 1;
	g->player.dir_y = 0;
	g->player.plane_x = 0;
	g->player.plane_y = 0.66;
	g->player.rot = 0.021;
	g->player.speed = 0.04;
}

static int	check_lines(char **line)
{
	static int	count;
	int			len;
	int			i;

	if (!count)
		count = 0;
	len = count_word(*line, ' ');
	if (count == 0)
		count = len;
	if ((count != len) || (len == 0))
		return (0);
	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] != ' ' && (*line)[i] != '\t')
			if (((*line)[i] < '0' || (*line)[i] > '9'))
				return (0);
	}
	return (1);
}

int			check_map(t_global *g)
{
	int		ret;
	char	*line;

	if (!(g->fd = open(g->name, O_RDONLY)))
		error("Error : coudn't open map.");
	line = NULL;
	if ((ret = get_next_line(g->fd, &line)) < 0)
		error("Error : map file invalid.");
	init_player(g, line);
	ft_strdel(&line);
	g->max_y = 0;
	while ((ret = get_next_line(g->fd, &line)) > 0)
	{
		if ((check_lines(&line)) != 1)
			return (0);
		g->max_y++;
		ft_strdel(&line);
	}
	if ((close(g->fd)) == -1 || g->max_y < 3)
		return (0);
	if ((g->fd = open(g->name, O_RDONLY)) == -1)
		return (0);
	return (1);
}
