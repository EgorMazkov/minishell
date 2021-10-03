/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ghumbert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:51:13 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/03 16:22:52 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*check_path(t_ms *minishell)
{
	char	*way;
	int		check;

	check = check_bin(minishell);
	if (check)
		return (ft_strdup(minishell->line[0]));
	else
	{
		get_path(minishell);
		way = right_way(minishell);
		return (way);
	}
	return (0);
}

char	**record_cmd2(t_ms *minishell)
{
	int		i;
	char	**dest;
	char	**line;

	line = malloc(sizeof(char *) * 1);
	line[0] = malloc(sizeof(char *) * ft_strlen(minishell->line[0]));
	line[0] = ft_strdup(minishell->line[0]);
	i = 0;
	while (minishell->line[i] && *minishell->line[i] != '|')
		i++;
	dest = (char **)malloc(sizeof(char *) * i);
	minishell->line[0] = check_path(minishell);
	if (minishell->line[0] == NULL)
	{
		printf("\033[0;31mDungeonMaster: \033[0;29m%s: ", line[0]);
		printf("\033[0;34mcommand not found 🤔\n");
		exit (0);
	}
	i = 0;
	while (minishell->line[i] && *minishell->line[i] != '|')
	{
		dest[i] = ft_strdup(minishell->line[i]);
		i++;
	}
	dest[i] = NULL;
	if (minishell->line[i] && *minishell->line[i] == '|')
		minishell->line = jopa(minishell, i);
	return (dest);
}

int	len_tab(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

char	**jopa(t_ms *minishell, int i)
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
