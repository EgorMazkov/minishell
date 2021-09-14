/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:45:18 by ghumbert          #+#    #+#             */
/*   Updated: 2021/08/08 13:45:19 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lest;
	t_list	*dest;

	if (!f)
		return (NULL);
	lest = NULL;
	while (lst)
	{
		dest = ft_lstnew((*f)(lst->content));
		if (!dest)
		{
			ft_lstclear(&lest, del);
			return (NULL);
		}
		ft_lstadd_back(&lest, dest);
		lst = lst->next;
	}
	return (lest);
}
