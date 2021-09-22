/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:17:21 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/22 14:10:41 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	get_path(t_ms *minishell, char **ev)
{
	int	i;

	i = -1;
	while (ev[++i])
	{
		if (ft_strncmp(ev[i], "PATH=", 5) == 0)
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
		while (minishell->way[i])
	{
		if (minishell->line == NULL)
			return (NULL);
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
