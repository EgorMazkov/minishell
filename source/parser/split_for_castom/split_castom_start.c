/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_castom_start.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 21:50:08 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/23 23:00:32 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	chek_qoute(char const *s, int *i, int flag, char c)
{
	if ((s[*i + 1] == '\"' && flag == 34) || \
	(flag == 39 && s[*i + 1] == '\''))
	{
		(*i)++;
		if (s[*i + 1] == c)
			i++;
		return (1);
	}
	(*i)++;
	return (0);
}

size_t	cikl_two(char const *s, char c, int i, int flag)
{
	while (s[i])
	{
		if (flag)
		{
			if (!chek_qoute(s, &i, flag, c))
				continue ;
			return (i);
		}
		else
		{
			if (s[i + 1] != c)
				i++;
			else
			{
				i++;
				return (i);
			}
			continue ;
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

char	**record_mass(char const *s, char **mass, t_dollar *dollar, int *i)
{
	if (s[*i] == '\'')
	{
		mass[dollar->j] = ft_substr(s, *i, dollar->a);
		dollar->flag = 39;
	}
	else
	{
		mass[dollar->j] = ft_substr(s, *i, dollar->a);
		dollar->flag = 34;
	}
	*i += dollar->a;
	if (mass[dollar->j] == NULL)
		jango(mass, dollar->j);
	dollar->j++;
	dollar->flag = 0;
	return (mass);
}
