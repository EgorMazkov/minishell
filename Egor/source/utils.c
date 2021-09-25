/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:18:04 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/25 16:17:33 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	null_struct(t_ms *minishell, t_cmd *cmd)
{
	t_se *se;
	
	se = malloc(sizeof(t_se));
	minishell->argc = 0;
	minishell->argv = NULL;
	minishell->env = NULL;
	minishell->i = 0;
	minishell->input = NULL;
	minishell->line = NULL;
	minishell->way = NULL;
	cmd->file = NULL;
	cmd->util_cmd = NULL;
	se->start = 0;
	se->end = 0;
}

void	appropriation(int argc, char **argv, char **ev, t_ms *minishell)
{
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->env = ev;
}
