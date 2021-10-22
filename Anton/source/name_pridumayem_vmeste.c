#include "../include/minishell.h"

int parser_and_validator(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	minishell->env = env_from_lists(*env);
	record_cmd(cmd, minishell, env);
	cmd_run(cmd);
	path(cmd, minishell);
	if (check_heredoc(cmd) == 130 || (choose_reds(cmd) == -3 && !(*cmd)->back && !(*cmd)->next)) /* Сделать отдельное условие для << */
	{
		g_parms.gexit = 1;
		return (1);
	}
	three_hundred_bucks(cmd, env);
	return (0);
}

void run_bash_command_from_exec(t_cmd **cmd, t_env **env)
{
	int out;
	pid_t pid;

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
	if (g_parms.gexit == 130)
	{
		g_parms.gexit = 1;
		return (1);
	}
	return (0);
}

void	exec(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	int	built_ex;
	g_parms.fd0_copy = dup(0);
	g_parms.fd1_copy = dup(1);
	if (parser_and_validator(cmd, minishell, env))
		return;
	if (!(*cmd)->next && !(*cmd)->back)
		built_ex = built_in_run(*cmd, env);
	if ((*cmd)->next || (*cmd)->back)
	{
		pipes(*cmd, env);
		warning_exit();
	}
	else if (built_ex == -1)
		g_parms.gexit = 1;
	else if (built_ex == 1)
		g_parms.gexit = 0;
	else if (!*cmd || !(*cmd)->argv || !*(*cmd)->argv)
		return;
	else if (*(*cmd)->argv && !is_builtin(*(*cmd)->argv))
		run_bash_command_from_exec(cmd, env);
	swapping_fd(g_parms.fd0_copy, g_parms.fd1_copy);
}
