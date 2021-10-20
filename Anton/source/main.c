#include "../include/minishell.h"

int g_exit;

void cmd_c_sl(int signum)
{
	(void)signum;
	printf("Quit :3\n");
}

void cmd_c_fork(int signum)
{
	(void)signum;
	// g_param->ret = 1;
	g_exit = 130;
	write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
}

void cmd_c(int signum)
{
	(void)signum;
	// g_param->ret = 1;
	g_exit = 1;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int lenlist(t_cmd *list)
{
	int i;

	i = 0;
	while (list->back)
		list = list->back;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

int is_builtin(char *command)
{
	if (!command)
		return (0);
	if (!ft_strcmp("echo", command))
		return (1);
	else if (!ft_strcmp("unset", command))
		return (1);
	else if (!ft_strcmp("export", command))
		return (1);
	else if (!ft_strcmp("cd", command))
		return (1);
	else if (!ft_strcmp("exit", command))
		return (1);
	else if (!ft_strcmp("env", command))
		return (1);
	else if (!ft_strcmp("pwd", command))
		return (1);
	return (0);
}

int built_in_run(t_cmd *cmd, t_env **ev)
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


int value_redirect_why_rdct(int read, int write)
{
	if (read && write)
		return (RDCT_ALL);
	if (read && !write)
		return (RDCT_L);
	if (write && !read)
		return (RDCT_R);
	return (0);
}

int why_rdct(t_cmd *cmd)
{
	int read;
	int write;

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

void test(t_cmd **cmd)
{
	t_cmd *temp;
	int i = -1;
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (temp)
	{
		while (temp->argv[++i])
			printf("%s\n", temp->argv[i]);
		i = -1;
		while (temp->redicts && temp->redicts[++i])
			printf("%s\n", temp->redicts[i]);
		printf("----------------((Anton))------------------\n");
		temp = temp->next;
		i = -1;
	}
}

int get_descriptor_util(char **redir, int str, t_cmd *cmd)
{
	if (!ft_strcmp(redir[str], "<"))
	{
		if (rdct_l(redir, str, cmd) == -3)
			return (-3);
	}
	else if (!ft_strcmp(redir[str], ">"))
	{
		if (rdct_r(redir, str, cmd) == -3)
			return (-3);
	}
	else if (!ft_strcmp(redir[str], ">>"))
	{
		if (rdct_rr(redir, str, cmd) == -3)
			return (-3);
	}
	else if (!ft_strcmp(redir[str], "<<"))
	{
		if (rdct_ll(redir, str, cmd) == -3)
			return (-3);
	}
	return (0);
}

int get_descriptor(char **redir, t_cmd *cmd)
{
	int str;

	str = -1;
	if (redir && *redir)
	{
		while (redir[++str])
			if (get_descriptor_util(redir, str, cmd) == -3)
				return (-3);
	}
	return (0);
}

int choose_reds(t_cmd **cmd)
{
	t_cmd *lst;

	if (g_exit == 258)
		return (-3);
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	lst = *cmd;
	while (*cmd)
	{
		if (get_descriptor((*cmd)->redicts, *cmd))
			return (-3);
		*cmd = (*cmd)->next;
	}
	*cmd = lst;
	return (0);
}

void cmd_run(t_cmd **cmd)
{
	t_cmd *temp;
	char **ar;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (*cmd)
	{
		ar = (*cmd)->argv;
		if (!ar || !*ar)
		{
			*cmd = (*cmd)->next;
			continue;
		}
		(*cmd)->redicts = record_redicts(ar);
		if (!(*cmd)->redicts)
			break;
		(*cmd)->argv = rewrite_cmd(ar);
		free_argv(ar);
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
}

int run_heredoc(char **redict, t_cmd **cmd)
{
	int i;

	i = -1;
	if (redict && *redict)
	{
		while (redict[++i])
		{
			if (!ft_strcmp("<<", redict[i]))
			{
				rdct_left_dock(*cmd, redict[i + 1]);
				if (g_exit == 130)
					return (130);
			}
		}
	}
	return (0);
}

int check_heredoc(t_cmd **cmd)
{
	t_cmd *temp;

	// g_exit = 0;
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

int bucksonly(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] != '$')
			return (0);
	return (1);
}

void three_hundred_bucks(t_cmd **cmd, t_env **env)
{
	int i;
	char *temp;
	t_cmd *first_command;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	first_command = *cmd;
	while (*cmd)
	{
		i = -1;
		if (!(*cmd)->argv || !(*cmd)->argv[0])
		{
			*cmd = (*cmd)->next;
			continue;
		}
		while ((*cmd)->argv[++i])
		{
			if ((*cmd)->argv[i][0] == '\'')
			{
				temp = (*cmd)->argv[i];
				(*cmd)->argv[i] = ft_strtrim((*cmd)->argv[i], "\'");
				free_str(temp);
			}
			else if ((*cmd)->argv[i][0] == '\"')
			{
				temp = (*cmd)->argv[i];
				(*cmd)->argv[i] = ft_strtrim((*cmd)->argv[i], "\"");
				free_str(temp);
			}
			if (!ft_strcmp((*cmd)->argv[i], "$?"))
			{
				temp = (*cmd)->argv[i];
				(*cmd)->argv[i] = ft_itoa(g_exit);
				free(temp);
				continue;
			}
			if ((*cmd)->argv[i][0] == '$')
			{
				temp = (*cmd)->argv[i];
				if (bucksonly(temp))
					break;
				(*cmd)->argv[i] = ft_strdup(get_variable_env(*env, (*cmd)->argv[i] + 1));
				// printf("%s\n", (*cmd)->argv[i]);
				free(temp);
			}
		}
		*cmd = (*cmd)->next;
	}
	*cmd = first_command;
}

void exec(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	pid_t pid;
	int built_ex;
	int fd0_copy = dup(0);
	int fd1_copy = dup(1);
	// int rct = open("rct",  O_WRONLY | O_TRUNC | O_CREAT, 0666);

	minishell->env = env_from_lists(*env);
	// int i = 0;
	// while (minishell->line[i])
	// {
	// 	printf("%s\n", minishell->line[i]);
	// 	i++;
	// }
	// return ;
	record_cmd(cmd, minishell, env);
	cmd_run(cmd);
	path(cmd, minishell);
	// free_minishell(minishell);
	if (check_heredoc(cmd) == 130 || (choose_reds(cmd) == -3 && !(*cmd)->back && !(*cmd)->next)) /* Сделать отдельное условие для << */
	{
		g_exit = 1;
		return;
	}
	three_hundred_bucks(cmd, env);
	// test(cmd);
	// return ;
	// rdct_left_dock(*cmd);
	if (!(*cmd)->next && !(*cmd)->back)
		built_ex = built_in_run(*cmd, env);
	if ((*cmd)->next || (*cmd)->back)
		pipes(*cmd, env);
	else if (built_ex == -1)
		g_exit = 1;
	else if (built_ex == 1)
		g_exit = 0;
	else if (!*cmd || !(*cmd)->argv || !*(*cmd)->argv)
		return;
	else if (*(*cmd)->argv && !is_builtin(*(*cmd)->argv)) /*!отрабатывает лишняя команда*/
	{
		pid = fork();
		if (!pid)
		{
			// dup2(g_params->fd_read, 0);
			// close(g_params->fd_read);
			if (0)
			{
				exit(0);
			}
			if (execve((*cmd)->argv[0], (*cmd)->argv, env_from_lists(*env)) == -1)
			{
				perror((*cmd)->argv[0]);
				exit(127);
			}
		}
		else
		{
			int out;
			waitpid(0, &out, 0);
			if (WIFEXITED(out))
				g_exit = WEXITSTATUS(out);
			// close(g_params->fd_read);
		}
	}
	/* Закрыть редиректы если нет команды а то текут заливают место занимают */
	dup2(fd0_copy, 0);
	close(fd0_copy);
	dup2(fd1_copy, 1);
	close(fd1_copy);
}

void go_readline_go(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	if (!minishell->input)
	{
		free_cmd(cmd);
		free_minishell(minishell);
		printf("exit\n");
		exit(0);
	}
	if (*minishell->input)
		add_history(minishell->input);
	if (minishell->input[0])
	{
		minishell->line = ft_split_for_minishell(minishell->input, ' ');
		exec(cmd, minishell, env);
		printf("\033[3;34mEXITCODE:    %d\n\033[0;29m", g_exit);
	}
}

int main(int argc, char **argv, char **ev)
{
	t_cmd *cmd;
	t_env *env = NULL;
	t_ms *minishell;

	(void)argc, (void)argv;
	minishell = NULL;
	cmd = NULL;
	if (!env_to_lists(&env, ev))
		return (0);
	while (1)
	{
		signal(SIGINT, cmd_c);
		signal(SIGQUIT, SIG_IGN);
		minishell = (t_ms *)malloc(sizeof(t_ms));
		null_struct(minishell, ev);
		minishell->input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		// minishell->input = ft_strdup("pwd");
		signal(SIGINT, cmd_c_fork);
		signal(SIGQUIT, cmd_c_sl);
		go_readline_go(&cmd, minishell, &env);
		free_cmd(&cmd);
		free_minishell(minishell);
		free(minishell);
	}
	free_env(&env);
}
// export a+=b
//  fd = open("our way",  O_WRONLY | O_TRUNC | O_CREAT, 0666);
