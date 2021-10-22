/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_pridumayem_vmeste.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 21:58:52 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/22 23:36:50 by ghumbert         ###   ########.fr       */
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

void	three_hundred_bucks_util(t_cmd **cmd, int i)
{
	char	*temp;
	int		j;

	j = 0;
	while ((*cmd)->argv)
	{
		while ((*cmd)->argv[i][j])
		{
			if ((*cmd)->argv[i][j] == '$')
			{
				j++;
				continue ;
			}
			if ((*cmd)->argv[i][0] == '\'')
			{
				temp = (*cmd)->argv[i];
				(*cmd)->argv[i] = ft_strtrim((*cmd)->argv[i], "\'");
				free_str(temp);
				return ;
			}
			else if (((*cmd)->argv[i][0] == '\"' && \
			((*cmd)->argv[i][1] == '\"' || (*cmd)->argv[i][1] == '\'')))
			{
				temp = (*cmd)->argv[i];
				(*cmd)->argv[i] = ft_strtrim((*cmd)->argv[i], "\"");
				free_str(temp);
				return ;
			}
			j++;
		}
		if ((*cmd)->argv[i + 1])
		{
			i++;
			j = 0;
		}
		else
			return ;
	}
	if ((*cmd)->next)
		*cmd = (*cmd)->next;
}

void	dollar(t_cmd **cmd, t_env **env)
{
	t_dollar dollar;
	char *temp;

	null_dollar(&dollar);
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	torsion_cmd(cmd, &dollar);
	if (!dollar.flag)
		return ;
	if (!ft_strcmp((*cmd)->argv[dollar.i], "$?"))
	{
		temp = (*cmd)->argv[dollar.i];
		(*cmd)->argv[dollar.i] = ft_itoa(g_exit);
		free(temp);
	}
	trimmer(cmd, &dollar, env);
}

int parser_and_validator(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	minishell->env = env_from_lists(*env);
	record_cmd(cmd, minishell, env);
	if (!validator(*cmd))
	{
		printf("Error bleat\n");
		return (1);
	}
	cmd_run(cmd);
	path(cmd, minishell);
	if (check_heredoc(cmd) == 130 || (choose_reds(cmd) == -3 && !(*cmd)->back && !(*cmd)->next)) /* Сделать отдельное условие для << */
	{
		g_exit = 1;
		return (1);
	}
	test(cmd);
	three_hundred_bucks_util(cmd, 0);
	dollar(cmd, env);
	test(cmd);
	
	return (0);
}

void run_bash_command_from_exec(t_cmd **cmd, t_env **env)
{
	int out;
	pid_t pid;

	pid = fork();
	if (pid < 0)
	{
		g_exit = 1;
		perror("fork");
		return ;
	}
	if (!pid)
	{
		if (execve((*cmd)->argv[0], (*cmd)->argv, env_from_lists(*env)) == -1)
		{
			perror((*cmd)->argv[0]);
			exit(127);
		}
	}
	else
	{
		waitpid(0, &out, 0);
		if (WIFEXITED(out))
			g_exit = WEXITSTATUS(out);
		// close(g_params->fd_read);
	}
}



void	swapping_fd(int fd0_copy, int fd1_copy)
{
	dup2(fd0_copy, 0);
	close(fd0_copy);
	dup2(fd1_copy, 1);
	close(fd1_copy);
}

int warning_exit(void)
{
	if (g_exit == 130)
	{
		g_exit = 1;
		return (1);
	}
	return (0);
}

void exec(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	int built_ex;
	int fd0_copy = dup(0);
	int fd1_copy = dup(1);
	// int rct = open("rct",  O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (parser_and_validator(cmd, minishell, env))
		return;
	// rdct_left_dock(*cmd);
	// test(cmd);
	// return ;
	if (!(*cmd)->next && !(*cmd)->back)
		built_ex = built_in_run(*cmd, env);
	if ((*cmd)->next || (*cmd)->back)
	{
		pipes(*cmd, env);
		warning_exit();
	}
	else if (built_ex == -1)
		g_exit = 1;
	else if (built_ex == 1)
		g_exit = 0;
	else if (!*cmd || !(*cmd)->argv || !*(*cmd)->argv)
		return;
	else if (*(*cmd)->argv && !is_builtin(*(*cmd)->argv)) /*!отрабатывает лишняя команда*/
		run_bash_command_from_exec(cmd, env);
	swapping_fd(fd0_copy, fd1_copy);
}