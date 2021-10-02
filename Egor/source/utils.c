/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:18:04 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/02 16:21:03 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	null_struct(t_ms *minishell, char **ev)
{
	minishell->input = NULL;
	minishell->line = NULL;
	minishell->env = ev;
}

