/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iporsenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 11:34:03 by iporsenn          #+#    #+#             */
/*   Updated: 2017/11/30 11:34:05 by iporsenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ret;
	t_list	*first;

	if (!lst || !f)
		return (NULL);
	ret = NULL;
	first = NULL;
	while (lst)
	{
		if (!first)
		{
			ret = f(ft_lstnew(lst->content, lst->content_size));
			first = ret;
		}
		else if (first)
		{
			ret->next = f(ft_lstnew(lst->content, lst->content_size));
			ret = ret->next;
		}
		lst = lst->next;
	}
	return (first);
}
