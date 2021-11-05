/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:57 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:19:58 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	rdct_r(char **redir, int str, t_cmd *cmd)
{
	if (cmd->fd_write != -1)
		close(cmd->fd_write);
	cmd->fd_write = open(redir[str + 1], O_WRONLY | \
	O_TRUNC | O_CREAT, 0666);
	if (cmd->fd_write == -1)
	{
		ft_str_err(redir[str + 1]);
		return (-3);
	}
	return (0);
}

int	rdct_rr(char **redir, int str, t_cmd *cmd)
{
	if (cmd->fd_write != -1)
		close(cmd->fd_write);
	cmd->fd_write = open(redir[str + 1], O_WRONLY | \
	O_CREAT | O_APPEND, 0666);
	if (cmd->fd_write == -1)
	{
		ft_str_err(redir[str + 1]);
		return (-3);
	}
	return (0);
}

int	rdct_l(char **redir, int str, t_cmd *cmd)
{
	if (cmd->fd_read != -1)
		close(cmd->fd_read);
	if (!access(redir[str + 1], 0))
		cmd->fd_read = open(redir[str + 1], O_RDONLY);
	else
	{
		cmd->fd_read = -999;
		ft_str_err(redir[str + 1]);
		return (-3);
	}
	return (0);
}

int	rdct_ll(char **redir, int str, t_cmd *cmd)
{
	if (cmd->fd_read != -1)
		close(cmd->fd_write);
	cmd->fd_read = cmd->fd_her;
	if (cmd->fd_read == -1)
	{
		ft_str_err(redir[str + 1]);
		return (-3);
	}
	return (0);
}
