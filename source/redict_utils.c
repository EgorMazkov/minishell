/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redict_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:20:01 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 17:13:58 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	value_redirect_why_rdct(int read, int write)
{
	if (read && write)
		return (RDCT_ALL);
	if (read && !write)
		return (RDCT_L);
	if (write && !read)
		return (RDCT_R);
	return (0);
}

int	why_rdct(t_cmd *cmd)
{
	int	read;
	int	write;

	read = 0;
	write = 0;
	if (cmd->fd_read == -999 || cmd->fd_write == -999)
		return (-999);
	if (cmd->fd_read != -1)
	{
		dup2(cmd->fd_read, 0);
		close(cmd->fd_read);
		read++;
	}
	if (cmd->fd_write != -1)
	{
		dup2(cmd->fd_write, 1);
		close(cmd->fd_write);
		write++;
	}
	return (value_redirect_why_rdct(read, write));
}

int	choose_reds(t_cmd **cmd)
{
	t_cmd	*lst;

	if (g_parms.gexit == 258)
		return (-3);
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	lst = *cmd;
	while (*cmd)
	{
		if (get_descriptor((*cmd)->redicts, *cmd) && \
		!(*cmd)->next && !(*cmd)->back)
			return (-3);
		*cmd = (*cmd)->next;
	}
	*cmd = lst;
	return (0);
}

int	run_heredoc(char **redict, t_cmd **cmd)
{
	int	i;

	i = -1;
	if (redict && *redict)
	{
		while (redict[++i])
		{
			if (!ft_strcmp("<<", redict[i]))
			{
				rdct_left_dock(*cmd, redict[i + 1]);
				if (g_parms.gexit == 130)
					return (130);
			}
		}
	}
	return (0);
}

int	check_heredoc(t_cmd **cmd)
{
	t_cmd	*temp;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (*cmd)
	{
		if (run_heredoc((*cmd)->redicts, cmd) == 130)
			return (130);
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
	return (0);
}
