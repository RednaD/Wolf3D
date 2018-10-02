/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:57:04 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/22 15:57:06 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char *dest;

	if (!s1)
		return (NULL);
	dest = 0;
	if (!(dest = ft_strnew(ft_strlen(s1))))
		return (NULL);
	ft_strcpy(dest, s1);
	return (dest);
}
