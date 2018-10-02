/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:58:45 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/22 15:58:47 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int		i;
	size_t	j;

	if (ft_strlen(s1) == 0)
	{
		ft_memcpy(s1, s2, n);
		s1[n] = '\0';
	}
	else
	{
		i = ft_strlen(s1);
		j = 0;
		while (s2[j] && j < n)
		{
			s1[i] = s2[j];
			i++;
			j++;
		}
		s1[i] = '\0';
	}
	return (s1);
}
