#include "../include/minishell.h"

void	redirects_close(t_cmd *cmd, t_pipe *pip)
{
	if (!pip->flag && cmd->next)
		pip->flag = 1;
	else if (pip->flag && cmd->next)
		pip->flag = 0;
	if (cmd->fd_her != -1)
		close(cmd->fd_her);
	if (cmd->fd_read != -1)
		close(cmd->fd_read);
	if (cmd->fd_her != -1)
		close(cmd->fd_write);
}

t_cmd	*pipe_parent_process(t_cmd *cmd, t_pipe *pip)
{
	if (!pip->flag && !cmd->next)
	{
		close(pip->a[0]);
		close(pip->b[1]);
	}
	else if (pip->flag && !cmd->next)
	{
		close(pip->a[1]);
		close(pip->b[0]);
	}
	if (!pip->flag)
	{
		if (pip->b[0])
			close(pip->b[0]);
		close(pip->a[1]);
	}
	else
	{
		if (pip->a[0])
			close(pip->a[0]);
		close(pip->b[1]);
	}
	redirects_close(cmd, pip);
	return (cmd->next);
}

//32 38