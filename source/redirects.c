/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:20:02 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 23:48:49 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	files_closes(t_cmd *cmd)
{
	while (cmd && cmd->back)
		cmd = cmd->back;
	while (cmd)
	{
		if (cmd->fd_read != -1)
			close(cmd->fd_read);
		if (cmd->fd_write != -1)
			close(cmd->fd_write);
		cmd = cmd->next;
	}
}

void	ctrl_wd(int signum)
{
	(void)signum;
	g_parms.gexit = 130;
}

void	loop_recording(char *stop, t_pipe pip)
{
	char	*input;

	while (1)
	{
		input = readline("\033[1;34mheredocccc $> \033[0;29m");
		if (!input || !ft_strcmp(input, stop))
		{
			free_str(input);
			break ;
		}
		ft_putstr_fd(input, pip.a[1]);
		write(pip.a[1], "\n", 1);
		free_str(input);
	}
	close(pip.a[1]);
	close(pip.a[0]);
	if (g_parms.gexit == 130)
		exit(130);
	else
	{
		exit(0);
	}
}

void	wait_input_and_record(t_cmd *cmd, t_pipe pip)
{
	int	out;

	out = 0;
	waitpid(0, &out, 0);
	if (WIFEXITED(out))
		g_parms.gexit = WEXITSTATUS(out);
	if (g_parms.gexit == 130)
	{
		close(pip.a[0]);
		close(pip.a[1]);
		while (cmd)
		{
			if (cmd->fd_her != -1)
				close(cmd->fd_her);
			cmd = cmd->back;
		}
	}
	else
	{
		close(pip.a[1]);
		if (cmd->fd_her != -1)
			close(cmd->fd_her);
		cmd->fd_her = pip.a[0];
	}
}

int	rdct_left_dock(t_cmd *cmd, char *stop)
{
	t_pipe	pip;
	void	*sgnl;

	sgnl = NULL;
	pipe(pip.a);
	pip.pid = fork();
	signal(SIGINT, ctrl_wd);
	signal(SIGQUIT, SIG_IGN);
	(sgnl = rl_getc_function);
	rl_getc_function = getc;
	if (!pip.pid)
		loop_recording(stop, pip);
	else
		wait_input_and_record(cmd, pip);
	(rl_getc_function = sgnl);
	signal(SIGINT, cmd_c_fork);
	return (RDCT_LL);
}
