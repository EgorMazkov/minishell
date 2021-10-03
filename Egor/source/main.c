/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:16:23 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/03 16:03:18 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	null_minishell(t_ms *minishell)
{
	free(minishell);
}

void test(t_cmd **cmd)
{
	t_cmd *temp;
	int i = -1;
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (temp)
	{
		while (temp->argv[++i])
			printf("%s\n", temp->argv[i]);
		printf("----------------((Anton))------------------\n");
		temp = temp->next;
		i = -1;
	}
}

int	main(int argc, char **argv, char **ev)
{
	t_ms	*minishell;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	minishell = NULL;
	cmd = NULL;
	while (1)
	{
		minishell = (t_ms *)malloc(sizeof(t_ms));
		null_struct(minishell, ev);
		minishell->input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		if (minishell->input[0])
			minishell->line = ft_split_for_minishell(minishell->input, ' ');
		if (!minishell->line)
			continue ;
		record_cmd(&cmd, minishell);
		test(&cmd);
		null_minishell(minishell);
	}
}
