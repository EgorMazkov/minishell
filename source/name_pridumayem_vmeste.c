/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_pridumayem_vmeste.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:18:29 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/24 00:13:54 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	null_dollar(t_dollar *dollar)
{
	dollar->a = 0;
	dollar->flag = 0;
	dollar->i = 0;
	dollar->j = 0;
}

int	parser_and_validator(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	free_argv(minishell->env);
	minishell->env = env_from_lists(*env);
	record_cmd(cmd, minishell, env);
	if (!validator(*cmd))
	{
		printf("\033[0;32mDungeonMaster\033[0;29m: Input not valid\n");
		g_parms.gexit = 257;
		return (1);
	}
	cmd_run(cmd);
	path(cmd, minishell);
	if (check_heredoc(cmd) == 130 || \
	(choose_reds(cmd) == -3 && !(*cmd)->back && !(*cmd)->next))
	{
		g_parms.gexit = 1;
		return (1);
	}
	three_hundred_bucks_util(cmd, 0);
	dollar(cmd, env);
	return (0);
}

void	run_bash_command_from_exec(t_cmd **cmd, t_env **env)
{
	int		out;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		g_parms.gexit = 1;
		ft_putstr_fd(strerror(errno), 1);
		return ;
	}
	if (!pid)
	{
		if (execve((*cmd)->argv[0], (*cmd)->argv, env_from_lists(*env)) == -1)
		{
			ft_str_err((*cmd)->argv[0]);
			exit(127);
		}
	}
	else
	{
		waitpid(0, &out, 0);
		if (WIFEXITED(out))
			g_parms.gexit = WEXITSTATUS(out);
	}
}

void	swapping_fd(int fd0_copy, int fd1_copy)
{
	dup2(fd0_copy, 0);
	close(fd0_copy);
	dup2(fd1_copy, 1);
	close(fd1_copy);
}

int	warning_exit(void)
{
	if (g_parms.gexit == 130)
	{
		g_parms.gexit = 1;
		return (1);
	}
	return (0);
}
