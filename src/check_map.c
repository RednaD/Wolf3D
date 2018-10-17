/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 17:44:07 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/16 16:02:11 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

int		check_borders(int **map, t_point start, int current_x, int current_y)
{
	if (!(map[current_y][current_x]))
		return (1);
	if (map[current_y][current_x] > 1)
		return (0);
	map[current_y][current_x] = 0;
	return (check_borders(map, start, current_x, current_y - 1)
			|| check_borders(map, start, current_x - 1, current_y)
			|| check_borders(map, start, current_x, current_y + 1)
			|| check_borders(map, start, current_x + 1, current_y));
}

void	check_start_pos(t_global *g)
{
	t_point		start;
	int			**tmp;
	int			i;

	start.x = g->player.pos_x;
	start.y = g->player.pos_y;
	if (g->map[start.y][start.x] == 0)
		error("Error : player spawn outside the map.");
	if (g->map[start.y][start.x] > 1)
		error("Error : player spawn in a wall.");
	tmp = (int**)malloc(sizeof(int*) + 1);
	i = -1;
	while (g->map[++i])
		ft_memcpy(tmp, g->map[i], g->max_y);
	tmp[i] = NULL;
	if (check_borders(tmp, start, start.x, start.y))
		error("Error : player spawn outside the map.");
	while (i > -1)
		free(tmp[i--]);
	free(tmp);
}

void	init_player(t_global *g, char *line)
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
	g->player.speed = 0.1;
	g->player.rot = 0.1;
}

int		check_lines(char **line)
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
			if (((*line)[i] < '0' || (*line)[i] > '9') && (*line)[i] != '-')
				return (0);
	}
	return (1);
}

int		check_map(t_global *g)
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
