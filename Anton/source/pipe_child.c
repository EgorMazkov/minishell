/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:59 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:20:00 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	last_command(t_pipe *pip)
{
	if (!pip->flag)
	{
		if (pip->was_red != RDCT_L && pip->was_red != RDCT_ALL)
			dup2(pip->b[0], 0);
	}
	else
	{
		if (pip->was_red != RDCT_L && pip->was_red != RDCT_ALL)
			dup2(pip->a[0], 0);
	}
}

int	first_command(t_pipe *pip)
{
	close(pip->a[0]);
	if (pip->was_red != RDCT_R && pip->was_red != RDCT_ALL)
		dup2(pip->a[1], 1);
	close(pip->a[1]);
	return (0);
}

void	mid_command(t_pipe *pip)
{
	if (!pip->flag)
	{
		if (pip->was_red != RDCT_L && pip->was_red != RDCT_ALL)
			dup2(pip->b[0], 0);
		close(pip->b[0]);
		close(pip->a[0]);
		if (pip->was_red != RDCT_R && pip->was_red != RDCT_ALL)
			dup2(pip->a[1], 1);
	}
	else if (pip->flag)
	{
		if (pip->was_red != RDCT_L && pip->was_red != RDCT_ALL)
			dup2(pip->a[0], 0);
		close(pip->a[0]);
		close(pip->b[0]);
		if (pip->was_red != RDCT_R && pip->was_red != RDCT_ALL)
			dup2(pip->b[1], 1);
	}
}

void	pipe_child_process(t_cmd *cmd, t_env **ev, t_pipe *pip)
{
	pip->was_red = why_rdct(cmd);
	if (pip->was_red == -999)
		exit(1);
	if (!cmd->next)
		last_command(pip);
	else if (!pip->flag && !cmd->back)
		first_command(pip);
	else if (!pip->flag || pip->flag)
		mid_command(pip);
	pip->exit_builtin = built_in_run(cmd, ev);
	if (g_parms.gexit == 130)
		exit(1);
	if (pip->exit_builtin == -1)
		exit(1);
	else if (pip->exit_builtin)
		exit(0);
	else
	{
		if (execve(cmd->argv[0], cmd->argv, env_from_lists(*ev)) == -1)
		{
			ft_putstr_fd(strerror(errno), 1);
			exit(127);
		}
	}
}
