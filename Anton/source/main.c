#include "../include/minishell.h"


t_params *g_params;

void cmd_c_sl(int signum)
{
	(void)signum;
	printf("Quit :3\n");
}

void	cmd_c_fork(int signum)
{
	(void)signum;
	// g_param->ret = 1;
	g_params->exit_code = 130;
	write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
}




void	cmd_c(int signum)
{
	(void)signum;
	// g_param->ret = 1;
	g_params->exit_code = 1;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int lenlist (t_cmd *list)
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

int is_builtin (char *command)
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


int built_in_run (t_cmd *cmd, t_env **ev)
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
			return(ft_export(ev, cmd->argv + 1));
		else if (!ft_strcmp("cd", cmd->argv[0]))
			return(ft_cd(cmd->argv[1], ev));
		else if (!ft_strcmp("exit", cmd->argv[0]))
			return(ft_exit(cmd->argv + 1));
		else if (!ft_strcmp("env", cmd->argv[0]))
			ft_env(*ev);
		else if (!ft_strcmp("pwd", cmd->argv[0]))
			return(ft_pwd(*ev));
		return (1);
	}
	return (0);
}


int why_rdct(t_cmd *cmd)
{
	int read;
	int write;

	read = 0;
	write = 0;
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
	if (read && write)
		return(RDCT_ALL);
	if (read && !write)
		return(RDCT_L);
	if (write && !read)
		return(RDCT_R);
	return (0);
}


// int redirects_for_pipe_fork(int *a, int *b, int flag, t_cmd *cmd)
// {
// 	if (!cmd->next)
// 	{
// 		if (!flag)
// 		{
// 			if (why_rdct(cmd) == RDCT_R || why_rdct(cmd) == RDCT_RR)
// 			{
// 				dup2(b[0], 0);
// 				return (1);
// 			}
// 			if (why_rdct(cmd) == RDCT_L || why_rdct(cmd) == RDCT_LL)
// 			{
// 				return (1);
// 			}
// 			// dup2(b[0], 0);
// 		}
// 		else
// 		{
// 			if (why_rdct(cmd) == RDCT_R || why_rdct(cmd) == RDCT_RR)
// 			{
// 				dup2(a[0], 0);
// 				return (1);
// 			}
// 			if (why_rdct(cmd) == RDCT_L || why_rdct(cmd) == RDCT_LL)
// 			{
// 				return (1);
// 			}
// 			// dup2(a[0], 0);
// 		}
// 		// execve(wc[0], wc, env);
// 	}
// 	else if (!flag && !cmd->back)
// 	{
// 		if (why_rdct(cmd) == RDCT_R || why_rdct(cmd) == RDCT_RR)
// 		{
// 			close(a[0]);
// 			close(a[1]);
// 			return (1);
// 		}
// 		if (why_rdct(cmd) == RDCT_L || why_rdct(cmd) == RDCT_LL)
// 		{
// 			close(a[0]);
// 			return (1);
// 		}
// 		// close(a[0]);
// 		// dup2(a[1], 1);
// 		// close(a[1]);
// 		return (0);
// 	}
// 	else if (!flag)
// 	{
// 		if (why_rdct(cmd) == RDCT_R || why_rdct(cmd) == RDCT_RR)
// 		{
// 			dup2(b[0], 0);
// 			close(a[0]);
// 			close(a[1]);
// 			return(1);
// 		}
// 		if (why_rdct(cmd) == RDCT_L || why_rdct(cmd) == RDCT_LL)
// 		{
// 			close(b[0]);
// 			close(a[0]);
// 			return (1);
// 		}
// 		// dup2(b[0], 0);
// 		// close(a[0]);
// 		// dup2(a[1], 1);
// 		return (0);
// 	}
// 	else if (flag)
// 	{
// 		if (why_rdct(cmd) == RDCT_R || why_rdct(cmd) == RDCT_RR)
// 		{
// 			dup2(a[0], 0);
// 			close(a[0]);
// 			close(b[0]);
// 			return (1);
// 		}
// 		if (why_rdct(cmd) == RDCT_L || why_rdct(cmd) == RDCT_LL)
// 		{
// 			close(a[0]);
// 			close(b[0]);
// 			dup2(b[1], 1);
// 			return (1);
// 		}
// 		dup2(a[0], 0);
// 		close(a[0]);//rvferrbrbr
// 		close(b[0]);
// 		dup2(b[1], 1);
// 	}
// 	return (0);
// }


void	pipes(t_cmd *cmd, t_env **ev)
{
	int a[2] = {0, 0};
	int b[2] = {0, 0};
	int flag;
	int len;
	int was_red;
	pid_t pid;
	flag = 0;
	len = lenlist(cmd);
	int exit_builtin;

	while (cmd->back)
		cmd = cmd->back;


	while (cmd)
	{
		if (cmd->next)
		{
			if (!flag)
				pipe(a);
			else
				pipe(b);
		}
		pid = fork();
		if (pid < 0)
		{
			strerror(-1);
			return ;
		}
		if (!pid)
		{
			was_red = why_rdct(cmd);
			if (!cmd->next)
			{
				if (!flag)
				{
					if (was_red != RDCT_L && was_red != RDCT_ALL)
						dup2(b[0], 0);
				}
				else
				{
					if (was_red != RDCT_L && was_red != RDCT_ALL)
						dup2(a[0], 0);
				}
			}
			else if (!flag && !cmd->back)
			{
				close(a[0]);
				if (was_red != RDCT_R && was_red != RDCT_ALL)
					dup2(a[1], 1);
				close(a[1]);
			}
			else if (!flag)
			{
				if (was_red != RDCT_L && was_red != RDCT_ALL)
					dup2(b[0], 0);
				close(b[0]);
				close(a[0]);
				if (was_red != RDCT_R && was_red != RDCT_ALL)
					dup2(a[1], 1);
			}
			else if (flag)
			{
				if (was_red != RDCT_L && was_red != RDCT_ALL)
					dup2(a[0], 0);
				close(a[0]);//rvferrbrbr
				close(b[0]);
				if (was_red != RDCT_R && was_red != RDCT_ALL)
					dup2(b[1], 1);
			}
			exit_builtin = built_in_run(cmd, ev);
			if (g_params->exit_code == 130)
			{
				exit(1);
			}
			if (exit_builtin == -1)
			{
				exit(1);
			}
			else if (exit_builtin)
			{
				exit(0);
			}
			else
			{
				if (execve(cmd->argv[0], cmd->argv, env_from_lists(*ev)) == -1)
				{
					perror(*cmd->argv);
					exit(127);
				}
			}
		}
		else
		{
			if (!flag && !cmd->next)
			{
				close(a[0]);
				close(b[1]);
			}
			else if (flag && !cmd->next)
			{
				close(a[1]);
				close(b[0]);
			}
			if (!flag)
			{
				if (b[0])
					close(b[0]);//tbbrbrvbrvr
				close(a[1]);
			}
			else
			{
				if (a[0])
					close(a[0]);//tkbmltgbkmtlbkm
				close(b[1]);
			}
			if (!flag && cmd->next)
				flag = 1;
			else if (flag && cmd->next)
				flag = 0;
			if (cmd->fd_her != -1)
				close(cmd->fd_her);
			if (cmd->fd_read != -1)
				close(cmd->fd_read);
			if (cmd->fd_her != -1)
				close(cmd->fd_write);
			cmd = cmd->next;
		}
	}

	int i = 0;//количество fork
		int out;
	while(i < len)
	{
		waitpid(0, &out, 0);
		if (WIFEXITED(out))
			g_params->exit_code = WEXITSTATUS(out);


		i++;
	}
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

int get_descriptor(char **redir, t_cmd *cmd)
{
	int str;

	str = -1;
	if (!redir || !*redir)//lkmgjbncjbwcwkmecnweec
	{
		return (0);//lkmgjbncjbwcwkmecnweec
	}//lkmgjbncjbwcwkmecnweec
	while (redir[++str])
	{
		if (!ft_strcmp(redir[str], "<"))
		{
			if (cmd->fd_read != -1)
				close(cmd->fd_read);
			cmd->fd_read = open(redir[str + 1], O_RDONLY);
			if (cmd->fd_read == -1)
			{
				perror(redir[str + 1]);
				return (-3);
			}
		}
		else if (!ft_strcmp(redir[str], ">"))
		{
			if (cmd->fd_write != -1)
				close(cmd->fd_write);
			cmd->fd_write = open(redir[str + 1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
			if (cmd->fd_write == -1)
			{
				perror(redir[str + 1]);
				return (-3);
			}
		}
		else if (!ft_strcmp(redir[str], ">>"))
		{
			if (cmd->fd_write != -1)
				close(cmd->fd_write);
			cmd->fd_write = open(redir[str + 1], O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (cmd->fd_write == -1)
			{
				perror(redir[str + 1]);
				return (-3);
			}
		}
		else if (!ft_strcmp(redir[str], "<<"))
		{
			if (cmd->fd_read != -1)
				close(cmd->fd_write);
			cmd->fd_read = cmd->fd_her;
			if (cmd->fd_read == -1)
			{
				perror(redir[str + 1]);
				return (-3);
			}
		}
	}
	return (0);
}


int choose_reds(t_cmd **cmd)
{
	t_cmd *lst;

	if (g_params->exit_code == 258)
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






int run_heredoc (char **redict, t_cmd **cmd)
{
	int i;

	i = -1;
	if (!redict || !*redict)//krbkmrfvnvnekljnedednvj
		return (0);//krbkmrfvnvnekljnedednvj
	while (redict[++i])
	{
		if (!ft_strcmp("<<", redict[i]))
		{
			rdct_left_dock(*cmd, redict[i + 1]);
			if (g_params->exit_code == 130)
				return (130);
		}
	}
	return (0);
}


int	check_heredoc (t_cmd **cmd)
{
	t_cmd *temp;

	// g_params->exit_code = 0;
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


int bucksonly (char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] != '$')
			return (0);
	return (1);
}


void three_hundred_bucks (t_cmd **cmd, t_env **env)
{
	int i;
	char *temp;
	t_cmd *first_command;
	int		quote = 0;;

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
				quote = 1;
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
				(*cmd)->argv[i] = ft_itoa(g_params->exit_code);
				free(temp);
				continue ;
			}
			if ((*cmd)->argv[i][0] == '$' && !quote)
			{
				temp = (*cmd)->argv[i];
				if (bucksonly(temp))
					break ;
				(*cmd)->argv[i] = ft_strdup(get_variable_env(*env, (*cmd)->argv[i] + 1));
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
	if (check_heredoc(cmd) == 130 || choose_reds(cmd) == -3)/* Сделать отдельное условие для << */
	{
		g_params->exit_code = 1;
		return ;
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
		g_params->exit_code = 1;
	else if (built_ex == 1)
		g_params->exit_code = 0;
	else if (!*cmd || !(*cmd)->argv || !*(*cmd)->argv)
		return ;
	else if (*(*cmd)->argv && !is_builtin(*(*cmd)->argv))/*!отрабатывает лишняя команда*/
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
				g_params->exit_code = WEXITSTATUS(out);
			// close(g_params->fd_read);
		}
	}
	/* Закрыть редиректы если нет команды а то текут заливают место занимают */
	dup2(fd0_copy, 0);
	close(fd0_copy);
	dup2(fd1_copy, 1);
	close(fd1_copy);
}


int main (int argc, char **argv, char **ev)
{
	t_cmd	*cmd;
	t_env *env = NULL;
	t_ms	*minishell;


	(void)argc, (void)argv;

	minishell = NULL;
	cmd = NULL;
	// pid_t pid;


	if (ev && *ev)
	{
		char *cw = getcwd(NULL, 0);
		env_record(&env, ev);
		overwrite_env(&env, "OLDPWD", cw);
		free(cw);
		cw = ft_itoa(ft_atoi(get_variable_env(env, "SHLVL")) + 1);
		overwrite_env(&env, "SHLVL", cw);
		free(cw);
	}
	else
	{
		unsigned long long i = 0;
		printf("which env?\n");
			char *say[5] = {"/usr/bin/say", "-v", "Yuri", "Где мой Ee Эн Вэ?", NULL};
		while (i < 100000)
		{
			if (i % 2 == 1)
				printf("\033[0;32m.\033[0;29m");
			i++;
		}
		printf("\nfuck you!\n");
			execve(say[0], say, ev);
		exit(1);
	}


	g_params = malloc(sizeof(t_params *));
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
		if (!minishell->input)
		{
			free_cmd(&cmd);
			free_minishell(minishell);
			printf("exit\n");
			break ;
		}
		if (*minishell->input)
			add_history(minishell->input);
		if (!check_quote(minishell))
		{
			free_str(minishell->input);
			free(minishell);
			printf("Error\n");
			continue ;
		}
		if (minishell->input[0])
		{
			minishell->line = ft_split_for_minishell(minishell->input, ' ');
			// int i = -1;
			// while (minishell->line[++i])
			// 	printf("%s\n", minishell->line[i]);
			// while (1);
			exec(&cmd, minishell, &env);
			printf("\033[3;34mEXITCODE:    %d\n\033[0;29m", g_params->exit_code);
		}
		// record_cmd(&cmd, minishell);
		// test(&cmd);
		// pipes(cmd, 123, ev);
		free_cmd(&cmd);
		free_minishell(minishell);
		free(minishell);

		// printf("%d\n", ft_strncmp("__CF_USER_TEXT_ENCOD", "V", 1));
	}
	free_env(&env);
	free(g_params);
}
	//export a+=b
	// fd = open("our way",  O_WRONLY | O_TRUNC | O_CREAT, 0666);
	