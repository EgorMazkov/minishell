/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:48:55 by ghumbert          #+#    #+#             */
/*   Updated: 2021/08/08 13:48:56 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] && i < len)
		i++;
	while (src[j] && (i + j + 1) < len)
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < len)
		dst[i + j] = '\0';
	return (i + ft_strlen((char *)src));
}
