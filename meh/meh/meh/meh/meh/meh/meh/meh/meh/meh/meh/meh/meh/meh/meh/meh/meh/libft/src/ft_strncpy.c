/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:59:12 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/22 15:59:14 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = ft_strlen(src);
	ft_bzero(dst, len);
	ft_memcpy(dst, src, len);
	if (len > i)
	{
		while (len != i)
		{
			dst[i] = '\0';
			i++;
		}
	}
	return (dst);
}
