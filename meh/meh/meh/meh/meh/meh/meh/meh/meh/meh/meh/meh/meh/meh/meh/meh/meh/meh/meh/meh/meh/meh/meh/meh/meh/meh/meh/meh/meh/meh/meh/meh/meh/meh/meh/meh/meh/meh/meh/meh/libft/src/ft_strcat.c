/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:56:10 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/22 15:56:11 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	int i;
	int j;
	int	len_s2;

	if (!s1 || !s2)
		return (0);
	i = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (i == 0)
	{
		ft_memcpy(s1, s2, len_s2);
		s1[len_s2] = '\0';
	}
	else
	{
		j = -1;
		while (s2[++j])
		{
			s1[i] = s2[j];
			i++;
		}
		s1[i] = '\0';
	}
	return (s1);
}
