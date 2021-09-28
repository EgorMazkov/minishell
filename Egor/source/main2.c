/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 19:07:32 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/28 19:19:07 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char    *double_quote(t_ms *minishell, t_se	*se)
{
    int j;
    int i;

    j = preparser(minishell, se);
    if (j)
    {
        while ()
    }
}

// echo "1 2 3"

int	main(int argc, char **argv, char **ev)
{
    t_ms	*minishell = NULL;
	t_cmd	cmd;
	t_se	*se = NULL;

    minishell = (t_ms *)malloc(sizeof(t_ms));
    se = null_struct(minishell, &cmd);
    // appropriation(argc, argv, ev, minishell);
    while (1)
    {
        minishell->input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
        if (minishell->input[0])
            minishell->line = ft_split(minishell->input, ' ');
    }
}