/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:18:04 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/18 12:18:05 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	null_struct(t_ms *minishell, t_cmd *cmd)
{
	minishell->argc = 0;
	minishell->argv = NULL;
	minishell->env = NULL;
	minishell->i = 0;
	minishell->input = NULL;
	minishell->line = NULL;
	minishell->way = NULL;
	cmd->file = NULL;
	cmd->util_cmd = NULL;
}

void	appropriation(int argc, char **argv, char **ev, t_ms *minishell)
{
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->env = ev;
}
