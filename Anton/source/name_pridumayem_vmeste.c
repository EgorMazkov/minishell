#include "../include/minishell.h"

int parser_and_validator(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	minishell->env = env_from_lists(*env);
	record_cmd(cmd, minishell, env);
	cmd_run(cmd);
	path(cmd, minishell);
	if (check_heredoc(cmd) == 130 || (choose_reds(cmd) == -3 && !(*cmd)->back && !(*cmd)->next)) /* Сделать отдельное условие для << */
	{
		g_exit = 1;
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