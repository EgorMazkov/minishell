#include "../include/minishell.h"


t_params *g_params;


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
	if (!cmd || !*cmd->argv)
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


void	pipes(t_cmd *cmd, int input, char **env, t_env **ev)
{
	// char *grep[] = {"/usr/bin/env", NULL};
	// char *grep[] = {"/bin/cat", "123", NULL};
	// char *wc[] = {"/usr/bin/wc", "-l", NULL};
	// char **inpt;
	int a[2];
	int b[2];
	int flag;
	int len;
	int was_red;
	(void)ev;
	pid_t pid;
	(void)input, (void)env;
	flag = 0;
	len = lenlist(cmd);
	int exit_builtin;

	while (cmd->back)
		cmd = cmd->back;

	// cmd->file = ft_strdup("<< eqw");
	// cmd->next->file = ft_strdup("< eqw");
	// cmd->next->next->file = ft_strdup(">> eqw");
	// cmd->next->next->next->next->file = ft_strdup("> eqw");


	// printf("Zahodi\t --------------------%d\n", why_rdct(cmd));

	int count = 0;
	while (cmd)
	{
		// int in = dup(0);
		// int out = dup(1);
		if (cmd->next)
		{
			if (!flag)
				pipe(a);
			else
				pipe(b);
		}
		// printf("pipe a:    %d, %d\n", a[0], a[1]);
		// printf("pipe b:    %d, %d\n", b[0], b[1]);
		// if (!cmd->back)//ervreververververrev
		// {
		// 	close(a[0]);
		// }
		pid = fork();
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
					// printf("Zahodi\t --------------------%d\n", why_rdct(cmd));
					if (was_red != RDCT_L && was_red != RDCT_ALL)
						dup2(a[0], 0);
				}
				// execve(wc[0], wc, env);
			}
			else if (!flag && !cmd->back)
			{
				// printf("Zahodi\t --------------------%d\n", why_rdct(cmd));
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
			// execve(grep[0], grep, env);
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
			// printf("PIOOEPE A:    %d, %d\n", a[0], a[1]);
			// printf("PIOOEPE B:    %d, %d\n", b[0], b[1]);
			cmd = cmd->next;
		}
	count++;
	}
	
	// if (pipe_orig != 0)
	// {
	// 	pipe(a);
	// 	pid = fork();
	// 	if (!pid)
	// 	{
	// 		close(a[0]);
	// 		dup2(a[1], 1);
	// 		close(a[1]);

	// 		execve(cat[0], cat, env);
	// 	}
	// }
	// close(a[1]);
	// pipe_orig--;
	// if (pipe_orig > 0)
	// {
	// 	pipe(b);
	// 	pid = fork();
	// 	if (!pid)
	// 	{
	// 		dup2(a[0], 0);
	// 		close(b[0]);
	// 		dup2(b[1], 1);
	// 		execve(grep[0], grep, env);
	// 	}
	// }
	// close(b[1]);
	// close(a[0]);
	// pipe_orig--;
	// if (1)
	// {
	// 	// pipe(fd);
	// 	pid = fork();
	// 	if (!pid)
	// 	{
	// 		dup2(b[0], 0);
	// 		execve(wc[0], wc, env);
	// 	}
	// 		close(b[0]);
	// }

	int i = 0;//количество fork
		int out;
	while(i < len)
	{
		waitpid(0, &out, 0);
		if (WIFEXITED(out))
			g_params->exit_code = WEXITSTATUS(out);
		// wait(0);
		// i++;


		i++;
	}
	// printf("\033[1;33mEXITCODE:    %d\n\033[0;29m", g_params->exit_code);
	// printf("%d\n", out);
	// printf("{ipe a:    %d, %d\n", a[0], a[1]);
	// printf("}ipe b:    %d, %d", b[0], b[1]);
}
/*
void	hardcode (char *input, t_built *built, char **ev, t_env **env)
{
	int pipe;
	t_cmd *cmd = NULL;
	pid_t	pid;

	char *minishell[] = {"/Users/tharodon/Desktop/minishell/Anton/./minishell", NULL};
	char *make[] = {"/usr/bin/make", NULL};
	char *makef[] = {"/usr/bin/make", "fclean", NULL};
	int qwer = 0;
		ladd(&cmd, new_cmd(3));
		ladd(&cmd, new_cmd(2));
		//
		while (qwer++ != 300)
			ladd(&cmd, new_cmd(1));

	// ladd(&cmd, new_cmd(2));
	// ladd(&cmd, new_cmd(2));
	// 	ladd(&cmd, new_cmd(1));


	if (is_pipes(input))
	{
		pipe = is_pipes(input);
		pipes(cmd, 0, ev);
		return ;
	}
	if (!ft_strncmp(input, "pwd", 4))
		ft_pwd(ev);
	else if (!ft_strncmp(input, "cd", 2))
		ft_cd(input + 3, env, built);
	else if (!ft_strncmp(input, "echo ", 5))
	{
		pipe = open("1234",  O_WRONLY | O_TRUNC | O_CREAT, 0666);
		qwer = dup(1);
		dup2(pipe, 1);
		close(pipe);
		// echo --- > 1234
		ft_echo(ft_split(input + 4, ' '));
		dup2(qwer, 1);
	}
	else if (!ft_strncmp(input, "env", 4))
		ft_env(*env);
	else if (!ft_strncmp(input, "export", 6))
		ft_export(env, ft_split(input + 6, ' ')[0]);
	else if (!ft_strncmp(input, "exit", 4))
	{
		printf("exit\n");
		free_all(env);
		exit(0);
	}
	else if (!ft_strncmp(input, "./minishell", 12))
	{
		pid = fork();
		if (!pid)
			execve(minishell[0], minishell, ev);
		else
			wait(&pid);
	}
	else if (!ft_strncmp(input, "make fcl", 8))
	{
		pid = fork();
		if (!pid)
			execve(makef[0], makef, ev);
		else
			wait(0);
	}
	else if (!ft_strncmp(input, "make", 4))
	{
		pid = fork();
		if (!pid)
			execve(make[0], make, ev);
		else
			wait(0);
	}
	else if (!ft_strncmp(input, "unset", 5))
		ft_unset(env, ft_split(input + 6, ' '));
	else
		printf("command not found: %s\n", input);
}*/
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


int redirect_count (char **argv)
{
	int count;
	int i;

	count = 0;
	i = -1;
	while (argv[++i])
		if (!ft_strcmp(argv[i], ">>") || \
		!ft_strcmp(argv[i], ">") || \
		!ft_strcmp(argv[i], "<") || \
		!ft_strcmp(argv[i], "<<"))
			count++;
	return (count * 2);
}


#include <string.h>
char **rewrite_cmd(char **argv)
{
	int i;
	int str;
	char **temp;

	i = 0;
	str = 0;
	temp = (char **)malloc((len_tab(argv) - redirect_count(argv) + 1) * sizeof(char *));
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], ">>") || \
		!ft_strcmp(argv[i], ">") || \
		!ft_strcmp(argv[i], "<") || \
		!ft_strcmp(argv[i], "<<"))
		{
			i += 2;
			continue;
		}
		temp[str] = strdup(argv[i]);
		str++;
		i++;
	}
	temp[str] = NULL;
	return (temp);
}


void	free_mass(char **argv)
{
	int i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
}


char**	record_redicts(char **argv)
{
	int str;
	int i;
	char **temp;

	str = 0;
	i = 0;
	temp = (char **)malloc((redirect_count(argv) + 1) * sizeof(char *));
	while (argv[str])
	{
		if (!ft_strcmp(argv[str], ">>") || \
		!ft_strcmp(argv[str], ">") || \
		!ft_strcmp(argv[str], "<") || \
		!ft_strcmp(argv[str], "<<"))
		{
			temp[i] = strdup(argv[str]);
			temp[i + 1] = strdup(argv[str + 1]);
			i += 2;
			str += 2;
			continue;
		}
		str++;
	}
	temp[i] = NULL;
	return (temp);
}


int get_descriptor(char **redir, t_cmd *cmd)
{
	int str;

	str = -1;
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



void	cmd_run(t_cmd **cmd)
{
	t_cmd *temp;
	char **ar;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (*cmd)
	{
		ar = (*cmd)->argv;
		(*cmd)->redicts = record_redicts(ar);
		(*cmd)->argv = rewrite_cmd(ar);
		*cmd = (*cmd)->next;
	}
	*cmd = temp;
}


int run_heredoc (char **redict, t_cmd **cmd)
{
	int i;

	i = -1;
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

	g_params->exit_code = 0;
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

void exec(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	pid_t pid;
	int built_ex;
	int fd0_copy = dup(0);
	int fd1_copy = dup(1);
	// int rct = open("rct",  O_WRONLY | O_TRUNC | O_CREAT, 0666);

	minishell->env = env_from_lists(*env);
	record_cmd(cmd, minishell, env);
	preparser_dollar(cmd, minishell);
	cmd_run(cmd);
	if (check_heredoc(cmd) == 130 || choose_reds(cmd) == -3)/* Сделать отдельное условие для << */
	{
		g_params->exit_code = 1;
		return ;
	}
	// test(cmd);
	// return ;
	// rdct_left_dock(*cmd);
	if (!(*cmd)->next && !(*cmd)->back)
		built_ex = built_in_run(*cmd, env);
	if ((*cmd)->next || (*cmd)->back)
		pipes(*cmd, 123, minishell->env, env);
	else if (built_ex == -1)
		g_params->exit_code = 1;
	else if (built_ex == 1)
		g_params->exit_code = 0;	
	else if (!built_ex)/*!отрабатывает лишняя команда*/
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
			if (execve((*cmd)->argv[0], (*cmd)->argv, minishell->env) == -1)
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

	// if (ev)
	// {
		env_record(&env, ev);
		overwrite_env(&env, "OLDPWD", getcwd(NULL, 0));
		overwrite_env(&env, "SHLVL", ft_itoa(ft_atoi(get_variable_env(env, "SHLVL")) + 1));
	// }
	g_params = malloc(sizeof(t_params *));
	while (1)
	{
		signal(SIGINT, cmd_c);
		signal(SIGQUIT, SIG_IGN);
		minishell = (t_ms *)malloc(sizeof(t_ms));
		null_struct(minishell, ev);
		minishell->input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		signal(SIGINT, cmd_c_fork);
		if (!minishell->input)
		{
			printf("exit\n");
			break ;
		}
		if (*minishell->input)
			add_history(minishell->input);
		if (!check_quote(minishell))
  		{
  			printf("Error\n");
  			continue ;
  		}
		if (minishell->input[0])
		{
			minishell->line = ft_split_for_minishell(minishell->input, ' ');
			exec(&cmd, minishell, &env);
			printf("\033[3;34mEXITCODE:    %d\n\033[0;29m", g_params->exit_code);
		}
		// record_cmd(&cmd, minishell);
		// test(&cmd);
		// pipes(cmd, 123, ev);
		cmd = NULL; // Clear cmd &7 minishell

		// printf("%d\n", ft_strncmp("__CF_USER_TEXT_ENCOD", "V", 1));
	}
}
	//export a+=b
	// fd = open("our way",  O_WRONLY | O_TRUNC | O_CREAT, 0666);
	