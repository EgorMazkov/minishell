#include "../include/minishell.h"


static void init_pipe_structure(t_pipe *pipe, t_cmd *cmd)
{
	pipe->flag = 0;
	pipe->exit_builtin = 0;
	pipe->len = lenlist(cmd);
	pipe->out = 0;
}


static void	the_pids_waiting(t_pipe pip)
{
	int out;

	while (pip.len--)
	{
		waitpid(0, &out, 0);
		if (WIFEXITED(out))
			g_exit = WEXITSTATUS(out);
	}
}


t_cmd	*go_back_cmd(t_cmd *cmd)
{
	while (cmd->back)
		cmd = cmd->back;
	return (cmd);
}

void pipes(t_cmd *cmd, t_env **ev)
{
	t_pipe pip;

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
			strerror(-1);
			return;
		}
		if (!pip.pid)
			pipe_child_process(cmd, ev, &pip);
		else
			cmd = pipe_parent_process(cmd, &pip);
	}
	the_pids_waiting(pip);
}
