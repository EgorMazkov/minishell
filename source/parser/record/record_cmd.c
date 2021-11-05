/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 15:51:21 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/20 16:10:57 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	record_cmd(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	int	i;
	int	check_pipe;

	if (!env)
		return ;
	i = 0;
	check_pipe = 0;
	while (minishell->line[i])
	{
		if (*minishell->line[i] == '|')
		{
			check_pipe = 1;
			record_cmd_pipe(cmd, minishell);
			break ;
		}
		i++;
	}
	if (check_pipe == 0)
		lst_add(cmd, new_cmd(minishell));
}

void	record_cmd_pipe(t_cmd **cmd, t_ms *minishell)
{
	int	i;

	i = 0;
	while (minishell->line[i])
	{
		while (minishell->line[i])
		{
			if (*minishell->line[i] == '|')
			{
				lst_add(cmd, new_cmd(minishell));
				i = 0;
				break ;
			}
			i++;
		}
	}
	lst_add(cmd, new_cmd(minishell));
}

char	**record_cmd2(t_ms *minishell)
{
	int		i;
	char	**dest;
	char	**line_array_shift;

	i = 0;
	while (minishell->line[i] && minishell->line[i][0] != '|')
		i++;
	dest = (char **)malloc((sizeof(char *) * i) + 1);
	i = 0;
	while (minishell->line[i] && minishell->line[i][0] != '|' && \
	*minishell->line[i] != '\0')
	{
		dest[i] = ft_strdup(minishell->line[i]);
		i++;
	}
	dest[i] = NULL;
	if (minishell->line[i] && *minishell->line[i] == '|')
	{
		line_array_shift = minishell->line;
		minishell->line = array_shift(minishell, i);
		free_argv(line_array_shift);
	}
	return (dest);
}
