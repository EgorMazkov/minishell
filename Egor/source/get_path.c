/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:17:21 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/02 16:21:07 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_path(t_ms *minishell)
{
	int	i;

	i = -1;
	while (minishell->env[++i])
	{
		if (ft_strncmp(minishell->env[i], "PATH=", 5) == 0)
			minishell->way = ft_split(minishell->env[i], ':');
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

char	*right_way(t_ms *minishell)
{
	int		i;
	int		fd;
	char	*res;

	i = 0;
	while (minishell->way || minishell->way[i])
	{
		if (minishell->way[i] == NULL)
			return (NULL);
		if (minishell->line == NULL)
			return (NULL);
		if (i == 0)
			res = slash_path(minishell->way[i] + 5, minishell->line[0]);
		else
			res = slash_path(minishell->way[i], minishell->line[0]);
		fd = open(res, O_RDONLY);
		free(res);
		if (fd != -1)
			break ;
		i++;
	}
	if (fd == -1)
		return (NULL);
	else
		return (res);
}
