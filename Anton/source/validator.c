/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:53:08 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/22 23:38:44 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validator_pipe(t_ms *minishell)
{
	if (minishell->line[0][0] == '|')
	{
		g_exit = 258;
		printf("\033[0;32mDungeonMaster\033[0;29m: syntax \
		error near unexpected token `|' \n");
		printf("\033[3;34mEXITCODE:    %d\n\033[0;29m", g_exit);
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
	if (cmd->argv[++(*i)] != NULL)
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
