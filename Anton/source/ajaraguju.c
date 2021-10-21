#include "../include/minishell.h"

int	built_in_run(t_cmd *cmd, t_env **ev)
{
	if (!cmd || !cmd->argv || !*cmd->argv)
		return (-999);
	if (!cmd->back && !cmd->next)
		why_rdct(cmd);
	if (is_builtin(cmd->argv[0]))
	{
		if (!ft_strcmp("echo", cmd->argv[0]))
			ft_echo(cmd->argv + 1);
		else if (!ft_strcmp("unset", cmd->argv[0]))
			ft_unset(ev, cmd->argv + 1);
		else if (!ft_strcmp("export", cmd->argv[0]))
			return (ft_export(ev, cmd->argv + 1));
		else if (!ft_strcmp("cd", cmd->argv[0]))
			return (ft_cd(cmd->argv[1], ev));
		else if (!ft_strcmp("exit", cmd->argv[0]))
			return (ft_exit(cmd->argv + 1));
		else if (!ft_strcmp("env", cmd->argv[0]))
			ft_env(*ev);
		else if (!ft_strcmp("pwd", cmd->argv[0]))
			return (ft_pwd(*ev));
		return (1);
	}
	return (0);
}

void	cmd_run(t_cmd **cmd)
{
	t_cmd		*temp;
	char		**ar;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (*cmd)
	{
		ar = (*cmd)->argv;
		if (!ar || !*ar)
		{
			*cmd = (*cmd)->next;
			continue ;
		}
		(*cmd)->redicts = record_redicts(ar);
		if (!(*cmd)->redicts)
			break ;
		(*cmd)->argv = rewrite_cmd(ar);
		free_argv(ar);
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
}
