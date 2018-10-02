/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:54:34 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/22 15:54:37 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memalloc(size_t size)
{
	void *tmp;

	tmp = NULL;
	if (!(tmp = (malloc(size))))
		return (NULL);
	ft_bzero(tmp, size);
	return (tmp);
}
