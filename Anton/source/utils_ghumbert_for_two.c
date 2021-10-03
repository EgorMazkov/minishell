/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ghumbert_for_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:57:22 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/03 15:57:23 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_bin(t_ms *minishell)
{
	int	i;

	i = 0;
	if (minishell->line)
	{
		if (!ft_strncmp(minishell->line[i], "cd", 2))
			return (1);
		if (!ft_strncmp(minishell->line[i], "env", 3))
			return (1);
		if (!ft_strncmp(minishell->line[i], "echo", 4))
			return (1);
		if (!ft_strncmp(minishell->line[i], "pwd", 3))
			return (1);
		if (!ft_strncmp(minishell->line[i], "unset", 5))
			return (1);
		if (!ft_strncmp(minishell->line[i], "exit", 4))
			return (1);
		if (!ft_strncmp(minishell->line[i], "export", 6))
			return (1);
	}
	return (0);
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

void	record_cmd(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	int	i;
	int	check_pipe;

	(void)env;

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

t_cmd	*new_cmd(t_ms *minishell)
{
	t_cmd	*el;
	int		j;

	j = 0;
	el = (t_cmd *)malloc(sizeof(t_cmd));
	if (!el)
		return (NULL);
	el->util_cmd = NULL;
	el->file = NULL;
	el->next = NULL;
	el->back = NULL;
	el->operator = -999;
	el->argv = record_cmd2(minishell);
	return (el);
}
