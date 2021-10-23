/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_castom_finish.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:24:38 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/22 16:00:46 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*jango(char **j, size_t i)
{
	while (i >= 0 && j[i])
	{
		free(j[i]);
		i--;
	}
	free(j);
	return (NULL);
}

size_t	schet_two(char const *s, size_t i, size_t sep, char c)
{
	if (s[i] == 34 || s[i] == 39)
	{
		sep++;
		if (s[i] == 34)
		{
			while (s[i] != '\"')
				i++;
		}
		else
		{
			while (s[i] != '\'')
				i++;
		}
		while (s[i] == c)
		{
			if (s[i + 1] == '\0')
				return (sep);
			i++;
		}
	}
	return (i);
}

size_t	schet(char const *s, char c)
{
	size_t	i;
	size_t	sep;

	i = 0;
	sep = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[++i])
	{
		if (s[i] == 34 || s[i] == 39)
			schet_two(s, i, sep, c);
		else if (s[i] == c)
		{
			while (s[i] == c)
			{
				if (s[i + 1] == '\0')
					return (sep);
				i++;
			}
			i--;
			if (s[i + 1] != '\"' || s[i + 1] != '\'')
				sep++;
		}
	}
	return (sep);
}

size_t	len_word(const char *src, size_t start, char c)
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
