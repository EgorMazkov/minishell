/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:51:13 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/21 18:58:07 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_quote(t_ms *minishell)
{
	int	i;
	int	quote;
	int	duble_quote;

	quote = 0;
	duble_quote = 0;
	i = 0;
	while (minishell->input[i])
	{
		if (minishell->input[i] == '\"')
			duble_quote++;
		if (minishell->input[i] == '\'')
			quote++;
		i++;
	}
	if (duble_quote % 2 != 0)
		return (0);
	if (quote % 2 != 0)
		return (0);
	return (1);
}

void	lst_add(t_cmd **lst, t_cmd *el)
{
	if (!el)
		return ;
	if (!*lst)
	{
		*lst = el;
		return ;
	}
	el->back = *lst;
	(*lst)->next = el;
	*lst = el;
}

char	**array_shift(t_ms *minishell, int i)
{
	char	**dest;
	int		str;

	str = 0;
	dest = malloc(sizeof(char *) * len_tab(minishell->line + i + 1) + 1);
	i++;
	while (minishell->line[i] != '\0')
	{
		dest[str++] = ft_strdup(minishell->line[i]);
		i++;
	}
	dest[str] = NULL;
	return (dest);
}
