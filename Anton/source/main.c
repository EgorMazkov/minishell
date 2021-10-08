#include "../include/minishell.h"


void	cmd_c_fork(int signum)
{
	(void)signum;
	// g_param->ret = 1;
	write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
}

void	cmd_c(int signum)
{
	(void)signum;
	// g_param->ret = 1;
	write(1, "\n", 1);
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
	if (is_builtin(cmd->argv[0]))
	{
		if (!ft_strcmp("echo", cmd->argv[0]))
			ft_echo(cmd->argv + 1);
		else if (!ft_strcmp("unset", cmd->argv[0]))
			ft_unset(ev, cmd->argv + 1);
		else if (!ft_strcmp("export", cmd->argv[0]))
			ft_export(ev, cmd->argv + 1);
		else if (!ft_strcmp("cd", cmd->argv[0]))
			ft_cd(cmd->argv[1], ev);
		else if (!ft_strcmp("exit", cmd->argv[0]))
			exit(0);
		else if (!ft_strcmp("env", cmd->argv[0]))
			ft_env(*ev);
		else if (!ft_strcmp("pwd", cmd->argv[0]))
			ft_pwd(*ev);
		return (1);
	}
	return (0);
}


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
	(void)ev;
	pid_t pid;
(void)input, (void)env;
	flag = 0;
	len = lenlist(cmd);

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
		printf("pipe a:    %d, %d\n", a[0], a[1]);
		printf("pipe b:    %d, %d\n", b[0], b[1]);
		// if (!cmd->back)//ervreververververrev
		// {
		// 	close(a[0]);
		// }
		pid = fork();
		if (!pid)
		{
			if (!cmd->next)
			{
				if (!flag)
				{
					dup2(b[0], 0);
				}
				else
				{
					dup2(a[0], 0);
				}
				// execve(wc[0], wc, env);
			}
			else if (!flag && !cmd->back)
			{
				close(a[0]);
				dup2(a[1], 1);
				close(a[1]);
			}
			else if (!flag)
			{
				dup2(b[0], 0);
				close(a[0]);
				dup2(a[1], 1);
			}
			else if (flag)
			{
				dup2(a[0], 0);
				close(a[0]);//rvferrbrbr
				close(b[0]);
				dup2(b[1], 1);
			}
			if (built_in_run(cmd, ev))
			{
				exit(0);
			}
			else
				if (execve(cmd->argv[0], cmd->argv, env_from_lists(*ev)) == -1)
				{
					perror(*cmd->argv);
					exit(0);
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
			printf("PIOOEPE A:    %d, %d\n", a[0], a[1]);
			printf("PIOOEPE B:    %d, %d\n", b[0], b[1]);
			cmd = cmd->next;
		}
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
	while(i < len)
	{
		wait(0);
		i++;
	}
	printf("{ipe a:    %d, %d\n", a[0], a[1]);
	printf("}ipe b:    %d, %d", b[0], b[1]);
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
		printf("----------------((Anton))------------------\n");
		temp = temp->next;
		i = -1;
	}
}







void exec(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	pid_t pid;
	// int rct = open("rct",  O_WRONLY | O_TRUNC | O_CREAT, 0666);

	record_cmd(cmd, minishell, env);
	minishell->env = env_from_lists(*env);
	(*cmd)->file = ft_strdup("<< eqw");
	if ((*cmd)->next || (*cmd)->back)
		pipes(*cmd, 123, minishell->env, env);
	else if (!built_in_run(*cmd, env))
	{
		pid = fork();
		if (!pid)
		{
			// signal(SIGINT, cmd_c_fork);
			// signal(SIGQUIT, SIG_IGN);
			// int eqw0 = open("eqw",  O_RDONLY); /* < */
			// int eqw1 = open("qwe", O_WRONLY | O_CREAT | O_APPEND, 0666); /* >> */
			// int eqw1 = open("qwe", O_WRONLY | O_TRUNC | O_CREAT , 0666); /* > */
			// dup2(eqw0, 0);
			// dup2(eqw1, 1);
			if (01)
			{
				if (!ft_strcmp((*cmd)->file, "> eqw"))
				{

					rdct_right(*cmd);
				}
				if (!ft_strcmp((*cmd)->file, ">> eqw"))
				{
					
					rdct_right_append(*cmd);
				}
				if (!ft_strcmp((*cmd)->file, "< eqw"))
				{
					
					rdct_left_read(*cmd);
				}
				if (!ft_strcmp((*cmd)->file, "<< eqw"))
				{

					rdct_left_dock(*cmd);
				}
			}
			if (execve((*cmd)->argv[0], (*cmd)->argv, minishell->env) == -1)
			{
				perror((*cmd)->argv[0]);
				exit(0);
			}
		}
		else
			wait(NULL);
	}
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

	if (ev)
	{
		env_record(&env, ev);
		overwrite_env(&env, "OLDPWD", getcwd(NULL, 0));
	}
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
	