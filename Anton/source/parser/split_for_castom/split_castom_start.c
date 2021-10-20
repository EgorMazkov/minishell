/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_castom_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 21:50:08 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/20 19:28:59 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

size_t	cikl_two(char const *s, char c, size_t i)
{
	while (s[i] != c && s[i] != '\0')
	{
		if (s[i + 1] == '\"' || s[i + 1] == '\'')
		{
			i++;
			return (i);
		}
		i++;
	}
	return (i);
}

size_t	cikl_three(char const *s, size_t i, char **mass, size_t word)
{
	mass[word] = ft_substr(s, i, len_word(s, i, ' '));
	if (mass[word] == NULL)
		jango(mass, word);
	word++;
	return (word);
}

int	mass_word(char **mass, size_t word, char const *s, int i)
{
	if (s[i] == '\0')
	{
		mass[word] = NULL;
		return (1);
	}
	return (0);
}

static char	**cikl(char const *s, char c, size_t i, char **mass)
{
	size_t	word;

	word = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			if (s[i] == '\'')
				mass[word] = ft_substr(s, i, len_word(s, i + 1, '\'') + 2);
			else
				mass[word] = ft_substr(s, i, len_word(s, i + 1, '\"') + 2);
			i++;
			if (mass[word] == NULL)
				jango(mass, word);
			word++;
		}
		else if (s[i] != c)
			word = cikl_three(s, i, mass, word);
		i = cikl_two(s, c, i);
		if (mass_word(mass, word, s, i))
			return (mass);
		i++;
	}
	mass[word] = NULL;
	return (mass);
}

char	**ft_split_for_minishell(char const *s, char c)
{
	size_t	i;
	char	**mass;

	i = 0;
	if (!s)
		return (NULL);
	mass = (char **)malloc((schet(s, c) + 2) * sizeof(char *));
	if (mass == NULL)
		return (NULL);
	mass[schet(s, c)] = NULL;
	while (s[i] == c && s[i] != '\0')
	{
		if (s[i + 1] == '\0')
			return (mass);
		i++;
	}
	mass = cikl(s, c, i, mass);
	i = 0;
	return (mass);
}
