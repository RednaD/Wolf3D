/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 18:44:18 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/24 18:44:25 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned char	car;

	car = c;
	dest = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (!n)
		return (NULL);
	while (n > 0)
	{
		*dest = *source;
		if (*dest == car)
			return ((void *)dest + 1);
		n--;
		dest++;
		source++;
	}
	return (NULL);
}
