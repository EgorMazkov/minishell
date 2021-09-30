/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:18:04 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/30 14:52:21 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	null_struct(t_ms *minishell, char **ev)
{
	minishell->env = NULL;
	minishell->input = NULL;
	minishell->line = NULL;
	minishell->env = ev;
}

