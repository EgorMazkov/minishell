/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:16:23 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/18 13:57:23 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **ev)
{
	t_ms	minishell;
	t_cmd	cmd;
	int		a;

	a = 0;
	null_struct(&minishell, &cmd);
	appropriation(argc, argv, ev, &minishell);
	while (1)
	{
		minishell.input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		if (minishell.input[0])
			minishell.line = ft_split(minishell.input, ' ');
		get_path(&minishell, ev);
		*minishell.way = right_way(&minishell);
		if (*minishell.way == NULL)
			continue ;
		main_writing_to_char(&cmd, &minishell);
		print_mass(&cmd);
	}
}

void	main_writing_to_char(t_cmd *cmd, t_ms *minishell)
{
	int	i;
	int	j;
	int	len_for_line;

	i = 0;
	j = 1;
	len_for_line = ft_strlen(minishell->way[0]);
	cmd->argv = (char **)malloc(len_for_line);
	cmd->argv[i] = minishell->way[0];
	i++;
	while (minishell->line[j])
	{
		len_for_line = ft_strlen(minishell->line[j]);
		cmd->argv[i] = (char *)malloc(sizeof(char) * (len_for_line));
		cmd->argv[i] = minishell->line[j];
		i++;
		j++;
	}
}
