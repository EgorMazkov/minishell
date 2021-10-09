/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 13:48:01 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/13 12:47:43 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_malloc_error(char **dest, size_t j)
{
	while (j >= 0 && dest[j])
	{
		free(dest[j]);
		j--;
	}
	free(dest);
	return (NULL);
}

static	size_t	ft_kol_vo(char const *s, char c)
{
	size_t	i;
	size_t	sep;

	i = 0;
	sep = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
			{
				if (s[i + 1] == '\0')
					return (sep);
				i++;
			}
			sep++;
		}
		i++;
	}
	return (sep);
}

static	size_t	len_word(const char *src, size_t start, char c)
{
	size_t	i;

	i = 0;
	while (src[start] != c && src[start] != '\0')
	{
		start++;
		i++;
	}
	return (i);
}

static	char	**ft_split_two(char const *s, char c, size_t i, char **dest)
{
	size_t	j;

	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			dest[j] = ft_substr(s, i, len_word(s, i, c));
			if (dest[j] == NULL)
				ft_malloc_error(dest, j);
			j++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i] == '\0')
		{
			dest[j] = NULL;
			return (dest);
		}
		i++;
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**dest;

	i = 0;
	if (!s)
		return (NULL);
	dest = (char **)malloc((ft_kol_vo(s, c) + 2) * sizeof(char *));
	if (dest == NULL)
		return (NULL);
	dest[ft_kol_vo(s, c)] = NULL;
	while (s[i] == c && s[i] != '\0')
	{
		if (s[i + 1] == '\0')
			return (dest);
		i++;
	}
	dest = ft_split_two(s, c, i, dest);
	return (dest);
}
