/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:59 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 21:57:39 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	init_pipe_structure(t_pipe *pipe, t_cmd *cmd)
{
	pipe->flag = 0;
	pipe->exit_builtin = 0;
	pipe->len = lenlist(cmd);
	pipe->out = 0;
	pipe->a[0] = 0;
	pipe->a[1] = 0;
	pipe->b[0] = 0;
	pipe->b[1] = 0;
}

static void	the_pids_waiting(t_pipe pip)
{
	int	out;

	while (pip.len--)
	{
		waitpid(0, &out, 0);
		if (WIFEXITED(out))
			g_parms.gexit = WEXITSTATUS(out);
	}
}

t_cmd	*go_back_cmd(t_cmd *cmd)
{
	while (cmd->back)
		cmd = cmd->back;
	return (cmd);
}

void	crush_fork(t_pipe *pip)
{
	strerror(-1);
	if (pip->a[0])
		close(pip->a[0]);
	if (pip->a[1])
		close(pip->a[1]);
	if (pip->b[0])
		close(pip->b[0]);
	if (pip->b[1])
		close(pip->b[1]);
}

void	pipes(t_cmd *cmd, t_env **ev)
{
	t_pipe	pip;

	cmd = go_back_cmd(cmd);
	init_pipe_structure(&pip, cmd);
	while (cmd)
	{
		if (cmd->next)
		{
			if (!pip.flag)
				pipe(pip.a);
			else
				pipe(pip.b);
		}
		pip.pid = fork();
		if (pip.pid < 0)
		{
			crush_fork(&pip);
			return ;
		}
		if (!pip.pid)
			pipe_child_process(cmd, ev, &pip);
		else
			cmd = pipe_parent_process(cmd, &pip);
	}
	the_pids_waiting(pip);
}
