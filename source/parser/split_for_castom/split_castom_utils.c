/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_castom_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:14:41 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/23 23:09:43 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	**torsion_i(char const *s, char **mass, int i, t_dollar *dollar)
{
	dollar->a = i;
	while (s[dollar->a] != ' ' && s[dollar->a] != '\0')
		dollar->a++;
	dollar->a = dollar->a - i;
	mass = record_mass(s, mass, dollar, &i);
	dollar->a = i;
	return (mass);
}

static char	**cikl(char const *s, char c, int i, char **mass)
{
	t_dollar	dollar;

	null_dollar(&dollar);
	while (s[i])
	{
		if (s[i++] == c)
			continue ;
		i--;
		if (s[i] == '\"' || s[i] == '\'')
			mass = torsion_i(s, mass, i, &dollar);
		else if (s[i] != c)
		{
			dollar.j = cikl_three(s, i, mass, dollar.j);
			i = cikl_two(s, c, i, dollar.flag);
		}
		if (mass_word(mass, dollar.j, s, i))
			return (mass);
		if (dollar.a != 0)
			i = dollar.a;
		if (s[i++] == '\0')
			break ;
		dollar.a = 0;
	}
	mass[dollar.j] = NULL;
	return (mass);
}

char	**ft_split_for_minishell(char const *s, char c)
{
	int		i;
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
	return (mass);
}
