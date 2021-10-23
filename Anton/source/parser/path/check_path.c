/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:45:27 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/23 16:19:23 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
		{
			if (minishell->way)
				free_argv(minishell->way);
			minishell->way = NULL;
		}
	}
}

char	*slash_path(char *way, char *line)
{
	char	*res;
	char	*dest;

	dest = ft_strjoin("/", line);
	res = ft_strjoin(way, dest);
	free(dest);
	return (res);
}

void	free_way(t_ms *minishell)
{
	if (minishell->way)
		free_argv(minishell->way);
	minishell->way = NULL;
}

void	path_way(t_ms *minishell, t_cmd **cmd, char *dest)
{
	char	*line;

	line = NULL;
	if (minishell->way)
		line = right_way(*cmd, minishell);
	if (line && *line)
		record_list_cmd(dest, line, cmd);
}

void	path(t_cmd **cmd, t_ms *minishell)
{
	char	*line;
	char	*dest;

	line = NULL;
	dest = NULL;
	while (((*cmd)->argv && (*cmd)->argv[0]) || \
	((*cmd)->redicts && (*cmd)->redicts[0]))
	{
		get_path(minishell);
		if (is_builtin((*cmd)->argv[0]))
		{
			free_way(minishell);
			if (check_next_cmd(cmd))
				continue ;
			return ;
		}
		path_way(minishell, cmd, dest);
		if (check_next_cmd(cmd))
		{
			free_way(minishell);
			continue ;
		}
		free_way(minishell);
		return ;
	}
}
