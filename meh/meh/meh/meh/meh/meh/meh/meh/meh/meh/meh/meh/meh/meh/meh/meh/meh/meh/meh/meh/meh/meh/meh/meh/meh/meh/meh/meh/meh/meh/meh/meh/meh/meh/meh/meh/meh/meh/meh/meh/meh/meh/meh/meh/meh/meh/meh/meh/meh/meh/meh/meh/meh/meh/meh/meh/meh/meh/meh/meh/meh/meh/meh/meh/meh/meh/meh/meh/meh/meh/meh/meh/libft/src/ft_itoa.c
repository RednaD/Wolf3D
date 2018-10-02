/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 15:52:13 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/25 15:52:16 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int		ft_count_number(long n)
{
	int	cpt;

	cpt = 0;
	if (n < 0)
	{
		cpt++;
		n = n * -1;
	}
	if (n >= 0 && n < 10)
		return (cpt++);
	while (n)
	{
		cpt++;
		if (n >= 10)
			n = n / 10;
		else
			return (cpt++);
	}
	return (cpt);
}

char			*ft_itoa(int n)
{
	int		i;
	long	num;
	char	*ret;

	num = (long)n;
	i = ft_count_number(num);
	if (!(ret = ft_strnew(i)))
		return (NULL);
	if (num < 0)
	{
		ret[0] = '-';
		num = num * -1;
	}
	if (num < 10)
		ret[i] = num + 48;
	if (num >= 10)
	{
		while (num != 0 && --i >= 0)
		{
			ret[i] = num % 10 + 48;
			num = num / 10;
		}
	}
	return (ret);
}
