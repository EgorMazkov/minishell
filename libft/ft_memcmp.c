/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:46:05 by ghumbert          #+#    #+#             */
/*   Updated: 2021/08/08 13:46:07 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*p1;

	i = 0;
	if (n == 0)
		return (0);
	p = (unsigned char *)s1;
	p1 = (unsigned char *)s2;
	while (*p == *p1 && ++i < n)
	{
		p++;
		p1++;
	}
	return ((int)*p - *p1);
}
