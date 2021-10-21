/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 19:14:21 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/20 19:16:04 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

char	*right_way(t_cmd *cmd, t_ms *minishell)
{
	int		fd;
	int		i;
	char	*res;

	i = -1;
	while (minishell->way && minishell->way[++i])
	{
		if (minishell->way[i] == NULL)
			return (NULL);
		if (i == 0)
			res = slash_path(minishell->way[i] + 5, cmd->argv[0]);
		else
			res = slash_path(minishell->way[i], cmd->argv[0]);
		fd = open(res, O_RDONLY);
		if (fd != -1)
			break ;
		free(res);
	}
	if (fd == -1)
		return (NULL);
	else
	{
		close(fd);
		return (res);
	}
}
