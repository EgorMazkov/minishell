/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:16:51 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 23:49:13 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_parm	g_parms;

void	go_readline_go(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	if (!minishell->input)
	{
		free_cmd(cmd);
		free_minishell(minishell);
		printf("exit...\n");
		exit(0);
	}
	if (!check_quote(minishell))
	{
		printf("Error\n");
		return ;
	}
	if (*minishell->input)
		add_history(minishell->input);
	if (minishell->input[0])
	{
		minishell->input = space_between_redirect_and_file(minishell->input);
		minishell->line = ft_split_for_minishell(minishell->input, ' ');
		if (!minishell->line)
			return ;
		if (!validator_pipe(minishell))
			return ;
		exec(cmd, minishell, env);
	}
}

int	main(int argc, char **argv, char **ev)
{
	t_cmd	*cmd;
	t_env	*env;
	t_ms	*minishell;

	(void)argc, (void)argv;
	env = NULL;
	if (!env_to_lists(&env, ev))
		exit(1);
	while (1)
	{
		cmd = NULL;
		minishell = NULL;
		signal(SIGINT, cmd_c);
		signal(SIGQUIT, SIG_IGN);
		minishell = null_struct();
		minishell->input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		signal(SIGINT, cmd_c_fork);
		signal(SIGQUIT, cmd_c_sl);
		go_readline_go(&cmd, minishell, &env);
		files_closes(cmd);
		free_cmd(&cmd);
		free_minishell(minishell);
		free(minishell);
	}
	free_env(&env);
}
