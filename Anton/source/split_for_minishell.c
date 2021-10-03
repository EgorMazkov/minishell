/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_minishell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 21:50:08 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/03 13:37:14 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*jango (char **j, size_t i)
{
	while (i >= 0 && j[i])
	{
		free(j[i]);
		i--;
	}
	free(j);
	return (NULL);
}

static size_t	schet (char const *s, char c)
{
	size_t	i;
	size_t	sep;

	i = 0;
	sep = 0;
	while (s[i] == c && s[i] != '\0')
		i++;
	while (s[i])
	{
		// printf("%c\n", s[i]);
		if (s[i] == 34)
		{
			sep++;
			i++;
			while (s[i++] != '\"')
				;
			while (s[i] == c)
			{
				if (s[i + 1] == '\0')
					return (sep);
				i++;
			}
		}
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
		i++;
	}
	return (sep);
}

static	size_t	len_word (const char *src, size_t start, char c)
{
	size_t	i;

	i = 0;
	// if (src[start] == '\"')
	// {
	// 	start++;
	// 	i--;
	// }
	while (((src[start] != '\"' || src[start] == '\'') && src[start] != c) && src[start] != '\0')
	{
		// printf("src : %c\n", src[start]);
		start++;
		i++;
	}
	return (i);
}

static char	**cikl (char const *s, char c, size_t i, char **mass)
{
	size_t	word;
	int 	quote = 0;
	int		check_quote = 0;

	word = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			quote++;
			if (quote % 2 != 0)
			{
				if (s[i] == '\'')
				{
					mass[word] = ft_substr(s, i, len_word(s, i + 1, '\'') + 2);
					// printf("%s\n", mass[word]);
				}
				else
				{
					mass[word] = ft_substr(s, i, len_word(s, i + 1, '\"') + 2);
					// printf("%s\n", mass[word]);
				}
				if (mass[word] == NULL)
					jango(mass, word);
				word++;
				while ((s[i] != '\"' || s[i] != '\'' || s[i] != c) && s[i] != '\0' && check_quote != 2)
				{
					if (s[i] == '\"')
						check_quote++;
					// printf("%c\n", s[i]);
					i++;
				}
				if (check_quote == 1)
					return (NULL);
				// i++;
				// printf("%c\n", s[i]);
				quote++;
			}
		}
		else if (s[i] != c)
		{
			mass[word] = ft_substr(s, i, len_word(s, i, c));
			// printf("%s\n", mass[word]);
			if (mass[word] == NULL)
				jango(mass, word);
			word++;
		}
		// if (quote > 0)
		// {
		// 	while (s[i] != c && s[i] != '\0')
		// 	{
		// 		printf("s[i] : %c\n", s[i]);
		// 		i++;
		// 	}
		// 	continue;
		// }
		// else
		{
			while (s[i] != c && s[i] != '\0')
			{
				if (s[i + 1] == '\"' || s[i + 1] == '\'')
					break ;
				// printf("i daa : %c\n", s[i]);
				i++;
			}
		}
		if (s[i] == '\0')
		{
			mass[word] = NULL;
			return (mass);
		}
		i++;
	}
	mass[word] = NULL;
	return (mass);
}

char	**ft_split_for_minishell(char const *s, char c)
{
	size_t	i;
	int		check_quote = 0;
	int		check_double_quote = 0;
	char	**mass;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			check_double_quote++;
		if (s[i] == '\'')
			check_quote++;
		i++;
	}
	if (check_quote % 2 != 0)
		return (NULL);
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
	// while (mass[i])
	// {
	// 	printf("%s\n", mass[i]);
	// 	i++;
	// }
	return (mass);
}
// #include <stdio.h>
// int main ()
// {
// 	int i = -1;
// 	char **qwe = ft_split("echo -n\"1 2 3\" ANTON \"EGOR 1 8 godikovs\"", ' ');
// 	while (qwe[++i])
// 		printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%s$\n", qwe[i]);
// }