/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:59:34 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/22 15:59:35 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	j = 0;
	while (haystack[i] && needle[j] && i < len)
	{
		while (haystack[i] == needle[j] && i < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i - j]);
			i++;
			j++;
		}
		i = i - j + 1;
		j = 0;
	}
	return (NULL);
}
