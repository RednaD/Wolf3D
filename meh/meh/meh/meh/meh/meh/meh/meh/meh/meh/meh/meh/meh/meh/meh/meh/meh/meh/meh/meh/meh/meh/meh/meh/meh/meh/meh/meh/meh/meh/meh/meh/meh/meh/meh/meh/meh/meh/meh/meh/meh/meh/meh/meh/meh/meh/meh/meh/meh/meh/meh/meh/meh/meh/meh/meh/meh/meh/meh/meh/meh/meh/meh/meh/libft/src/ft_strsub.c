/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:00:07 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/22 16:00:08 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char *dest;

	dest = 0;
	if (!s)
		return (NULL);
	if (!(dest = ft_strnew(len)))
		return (NULL);
	ft_strncpy(dest, (s + start), (len));
	return (dest);
}
