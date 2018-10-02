/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 19:00:47 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/24 19:00:50 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (!len || src == dst)
		return (dest);
	else if (src > dst)
	{
		ft_memcpy(dest, source, len);
		return (dest);
	}
	else
	{
		while (len)
		{
			len--;
			dest[len] = source[len];
		}
		return (dest);
	}
	return (NULL);
}
