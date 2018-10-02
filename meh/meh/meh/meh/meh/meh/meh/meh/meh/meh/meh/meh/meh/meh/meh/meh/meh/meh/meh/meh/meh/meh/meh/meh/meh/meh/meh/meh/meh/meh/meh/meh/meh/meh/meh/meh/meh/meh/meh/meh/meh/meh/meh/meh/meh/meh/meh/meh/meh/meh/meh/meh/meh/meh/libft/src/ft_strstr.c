/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:59:56 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/22 15:59:58 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!needle[0])
		return ((char *)haystack);
	while (haystack[i] && needle[j])
	{
		while (haystack[i] == needle[j])
		{
			if (!needle[j + 1])
				return ((char *)&haystack[i - j]);
			i++;
			j++;
		}
		i = i - j + 1;
		j = 0;
	}
	return (NULL);
}
