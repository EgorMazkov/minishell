/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:53:08 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/23 23:48:59 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validator_pipe(t_ms *minishell)
{
	if (minishell->line[0][0] == '|')
	{
		g_parms.gexit = 258;
		printf("\033[0;32mDungeonMaster\033[0;29m: Input not valid\n");
		return (0);
	}
	return (1);
}

int	is_rdct(char *dest)
{
	if (!ft_strcmp(dest, ">>") || \
	!ft_strcmp(dest, ">") || \
	!ft_strcmp(dest, "<") || \
	!ft_strcmp(dest, "<<"))
		return (1);
	return (0);
}

int	valid_two(t_cmd **cmd, int *i)
{
	if ((*cmd)->next)
		(*cmd) = (*cmd)->next;
	else
		return (1);
	*i = 0;
	return (0);
}

int	val_three(t_cmd *cmd, int *i)
{
	if (cmd->argv[(*i)] != NULL)
		(*i)++;
	if (cmd->argv[*i] == NULL)
		return (0);
	return (1);
}

int	valid_four(t_cmd **cmd, int *i)
{
	if ((*cmd)->argv[*i] == NULL)
	{
		if ((*cmd)->next)
			(*cmd) = (*cmd)->next;
		*i = 0;
		return (1);
	}
	return (0);
}
