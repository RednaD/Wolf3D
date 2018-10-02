/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 11:48:00 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/25 11:48:03 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	car;

	i = 0;
	str = (unsigned char *)s;
	car = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == car)
			return (((void *)str) + i);
		i++;
	}
	return (NULL);
}
