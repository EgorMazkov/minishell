/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:17:21 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/03 15:49:27 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_path(t_ms *minishell)
{
	int	i;

	i = -1;
	if (!minishell->env)
	{
		minishell->way = NULL;
		return ;
	}
	while (minishell->env[++i])
	{
		if (ft_strncmp(minishell->env[i], "PATH=", 5) == 0)
		{
			minishell->way = ft_split(minishell->env[i], ':');
			break ;
		}
		else
			minishell->way = NULL;
	}
}

char	*slash_path(char *way, char *line)
{
	char	*res;

	line = ft_strjoin("/", line);
	res = ft_strjoin(way, line);
	free(line);
	return (res);
}

void	null_struct(t_ms *minishell, char **ev)
{
	minishell->input = NULL;
	minishell->line = NULL;
	minishell->env = ev;
}
