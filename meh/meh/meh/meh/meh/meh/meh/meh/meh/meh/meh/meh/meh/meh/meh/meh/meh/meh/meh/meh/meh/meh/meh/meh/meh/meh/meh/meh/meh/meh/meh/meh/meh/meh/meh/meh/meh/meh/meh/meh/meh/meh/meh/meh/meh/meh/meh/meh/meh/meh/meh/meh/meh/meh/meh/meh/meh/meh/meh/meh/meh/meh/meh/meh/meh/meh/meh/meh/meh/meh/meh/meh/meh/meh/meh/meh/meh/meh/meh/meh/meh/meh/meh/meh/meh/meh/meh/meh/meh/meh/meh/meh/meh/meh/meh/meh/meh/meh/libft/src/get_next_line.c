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

/*static char	*ft_strjoin_free(char *s1, const char *s2)
  {
  char	*dest;
  int		len;

  if (!s1 || !s2)
  return (0);
  dest = 0;
  len = ft_strlen(s1) + ft_strlen(s2);
  if (!(dest = ft_strnew(len)))
  return (NULL);
  ft_strcpy(dest, s1);
  ft_strcat(dest, (s2));
  ft_strdel(&s1);
  return (dest);
  }

  static int	read_reste(char **reste, char **line, size_t len)
  {
  int		i;
  int		end;
  char	tmp[len + 1];

  tmp[len] = '\0';
  end = 0;
  if (!(*line = ft_strnew(len)))
  return (-1);
  i = -1;
  while ((*reste)[++i] != '\n' && (*reste)[i] != '\0')
  (*line)[i] = (*reste)[i];
  if ((*reste)[i] == '\n')
  {
  end = 1;
  i++;
  }
  ft_bzero(tmp, len + 1);
  ft_strcpy(tmp, *reste + i);
  ft_strdel(reste);
  if (end == 1)
  {
 *reste = ft_strdup(tmp);
 return (1);
 }
 return (0);
 }

 static int	read_buff(char *buff, char **line, char **reste, size_t len)
 {
 int		i;
 char	tmp[len + 1];

 ft_bzero(tmp, len + 1);
 i = -1;
 while (buff[++i] != '\n' && buff[i])
 tmp[i] = buff[i];
 if (!(*line))
 {
 if (!(*line = ft_strdup(tmp)))
 return (0);
 }
 else
 *line = ft_strjoin_free(*line, tmp);
 if (buff[i] == '\n')
 {
 if (*reste)
 ft_strdel(reste);
 if (!(*reste = ft_strnew(len - i)))
 return (0);
 i++;
 ft_strcpy(*reste, buff + i);
 return (1);
}
return (0);
}

int			get_next_line(int fd, char **line)
{
	int			ret;
	char		buff[BUFF_SIZE + 1];
	static char	*reste = NULL;

	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	ret = 0;
	if (ft_strlen(reste))
		if (read_reste(&reste, line, ft_strlen(reste)) == 1)
			return (1);
	ft_bzero(buff, BUFF_SIZE + 1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (read_buff((char*)&buff, line, &reste, BUFF_SIZE) == 1)
			return (1);
	}
	if (!ft_strlen(reste) && ret == 0 && !ft_strlen(*line))
	{
		ft_strdel(&reste);
		return (0);
	}
	return (ret != -1) ? 1 : -1;
}
*/

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
