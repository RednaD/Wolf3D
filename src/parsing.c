/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:25:20 by iporsenn          #+#    #+#             */
/*   Updated: 2018/06/05 17:25:22 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf_3d.h"

static void		first_read(int fd, t_global *global)
{
	int		cpt;
	int		ret;
	int		tmp;
	char	*line;

	cpt = 0;
	ret = 0;
	tmp = 0;
	line = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if ((check_map(line, cpt, global, &tmp)) == 1)
		{
			cpt++;
			ft_strdel(&line);
		}
		else
			error("not a valid map");
	}
	if (tmp == 0)
		error("not a valid map");
	global->height = cpt;
	if ((close(fd)) == -1)
		error("closed() failed");
}

static void		*malloc_map(t_global *global, int len)
{
	int i;

	if (!(global->wall = (int**)ft_memalloc(sizeof(int*) * global->height)))
		return (NULL);
	i = -1;
	while (++i < global->height)
	{
		if (!(global->wall[i] = (int*)ft_memalloc(sizeof(int) * len)))
			return (NULL);
	}
	return (NULL);
}

static void		fill_tab(t_global *global, char **array, int y, int len_array)
{
	int x;

	x = -1;
	while (++x < len_array)
		global->wall[y][x] = ft_atoi(array[x]);
}

void			parsing(t_global *global, char *line)
{
	char		**array;
	int			len_array;
	static int	y = -1;

	len_array = count_word(line, ' ');
	y++;
	array = ft_strsplit(line, ' ');
	if (!global->wall)
		malloc_map(global, len_array);
	fill_tab(global, array, y, len_array);
	global->width = len_array;
	free_array(array, len_array);
}

int				launch_parse(t_global *global, int fd, char **av)
{
	int		ret;
	int		cpt;
	char	*line;

	ret = 0;
	cpt = 0;
	line = NULL;
	first_read(fd, global);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		error("open() failed");
	cpt = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		parsing(global, line);
		cpt++;
		ft_strdel(&line);
	}
	return (1);
}
