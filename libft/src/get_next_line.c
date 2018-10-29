/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 16:40:12 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/02 13:44:42 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strccut(char **src, char c)
{
	size_t	i;
	char	*dest;
	char	*tmp;

	if (!(**src) || !c)
		return (NULL);
	i = 0;
	while ((*src)[i] != '\0' && (*src)[i] != c)
		i++;
	if (i == ft_strlen(*src))
	{
		dest = ft_strdup(*src);
		ft_strclr(*src);
	}
	else
	{
		dest = ft_strsub(*src, 0, i);
		tmp = (*src);
		*src = ft_strsub(*src, i + 1, ft_strlen(*src));
		free(tmp);
	}
	return (dest);
}

int		ft_strrec(const char *str, char c)
{
	int i;
	int count;

	if (!str || !c)
		return (0);
	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}

int		get_next_line(const int fd, char **line)
{
	char		buffer[BUFF_SIZE + 1];
	char		*tmp;
	int			file;
	static char	*memory;

	if (fd < 0 || fd > 10000 || line == NULL)
		return (-1);
	if (!memory)
		memory = ft_strnew(0);
	*line = NULL;
	file = 1;
	while (!(ft_strrec(memory, '\n')) && file > 0)
	{
		if ((file = read(fd, buffer, BUFF_SIZE)) == -1)
			return (file);
		buffer[file] = '\0';
		tmp = memory;
		memory = ft_strjoin(memory, buffer);
		free(tmp);
	}
	if (!(*line = ft_strccut(&memory, '\n')))
		return (0);
	return ((file + ft_strlen(*line) != 0) ? 1 : 0);
}
