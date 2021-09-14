/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:49:58 by ghumbert          #+#    #+#             */
/*   Updated: 2021/08/08 13:50:01 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	i;
	size_t	a;

	i = 0;
	a = 0;
	if (need[0] == '\0')
		return ((char *)hay);
	while (hay[i] && i < len)
	{
		a = 0;
		while (i + a < len && hay[i + a] == need[a])
		{
			a++;
			if (!need[a])
				return ((char *)&hay[i]);
		}
		i++;
	}
	return (0);
}
