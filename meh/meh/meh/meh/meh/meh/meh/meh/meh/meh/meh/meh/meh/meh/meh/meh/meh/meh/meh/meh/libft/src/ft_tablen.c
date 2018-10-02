/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tablen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arusso <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 16:11:02 by arusso            #+#    #+#             */
/*   Updated: 2018/02/02 16:12:25 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_tablen(char **tab)
{
	int count;

	if (!tab)
		return (0);
	count = 0;
	while (tab[count])
		count++;
	return (count);
}
