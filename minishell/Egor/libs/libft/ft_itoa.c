/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:44:08 by ghumbert          #+#    #+#             */
/*   Updated: 2021/08/08 13:44:12 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static	unsigned int	ft_itoa_r(int n)
{
	unsigned int	i;
	unsigned int	nbr;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		nbr = n * -1;
		i++;
	}
	else
		nbr = n;
	while (nbr >= 1)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

static	char	*ft_itoa_e(char *dest, unsigned int nbr, unsigned int i)
{
	while (nbr > 0)
	{
		dest[i] = nbr % 10 + '0';
		nbr /= 10;
		i--;
	}
	return (dest);
}

char	*ft_itoa(int n)
{
	char				*dest;
	unsigned int		i;
	unsigned int		nbr;

	i = ft_itoa_r(n);
	dest = (char *)malloc((i + 1) * sizeof(char));
	if (!dest)
		return (0);
	dest[i] = '\0';
	i--;
	if (n < 0)
	{
		dest[0] = '-';
		nbr = n * (-1);
	}
	else if (n == 0)
	{
		dest[i] = '0';
		nbr = n;
	}
	else
		nbr = n;
	if (nbr > 0)
		return (ft_itoa_e(dest, nbr, i));
	return (dest);
}
