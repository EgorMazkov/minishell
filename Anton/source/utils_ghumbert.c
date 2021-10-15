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

int check_quote(t_ms *minishell)
{
 int i;
 int quote;
 int duble_quote;

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
	if (!minishell->line[0])
  		return (NULL);
	line[0] = malloc(sizeof(char *) * ft_strlen(minishell->line[0]));
	line[0] = ft_strdup(minishell->line[0]);
	i = 0;
	while (minishell->line[i] && *minishell->line[i] != '|')
		i++;
	dest = (char **)malloc(sizeof(char *) * i);
	minishell->line[0] = check_path(minishell);
	i = 0;
	if (minishell->line[0] == NULL)
	{
		minishell->line[0] = ft_strdup(line[0]);
		dest[i] = ft_strdup(line[0]);
		i++;
	}
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

	i = 0;
	while (str[i])
		i++;
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
