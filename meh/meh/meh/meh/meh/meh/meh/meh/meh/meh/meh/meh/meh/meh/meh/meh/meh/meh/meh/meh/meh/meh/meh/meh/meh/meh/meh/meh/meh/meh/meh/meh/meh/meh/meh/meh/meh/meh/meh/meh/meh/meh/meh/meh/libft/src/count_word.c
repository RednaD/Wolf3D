/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/10 14:15:09 by iporsenn          #+#    #+#             */
/*   Updated: 2018/10/01 16:42:33 by arusso           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int			count_word(const char *str, char c)
{
	int i;
	int count;

	i = 0;
	if (!str || !str[i])
		return (0);
	count = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
		{
			count++;
			i++;
		}
		else
			i++;
	}
	return (count);
/*	int i;
	int cpt;

	i = 0;
	cpt = 0;
	if (!s || !c)
		return (0);
	while (s[i])
	{
		if (s[i] == c && !s[i - 1])
			i++;
		if ((s[i - 1] != c && s[i] == c) || (!s[i + 1] && s[i] != c))
			cpt++;
		i++;
	}
	return (cpt);*/
}
