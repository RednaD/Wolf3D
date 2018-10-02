/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:57:45 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/22 15:57:47 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	tmp;
	int		j;

	if (size == 0)
		return (ft_strlen(src));
	i = ft_strlen(dst);
	tmp = ft_strlen(dst);
	j = 0;
	if (src[j] == '\0')
		return (i);
	if (i > size)
		return (ft_strlen(src) + size);
	while (i < size - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	if (size <= ft_strlen(src) || size >= i)
		return (tmp + ft_strlen(src));
	else
		return (i);
}
