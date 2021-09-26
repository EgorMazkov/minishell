#include "../include/minishell.h"


char **wc(void) //! DELeeeeeeeeeeeeTe
{
	char **wc;

	wc = (char **)malloc(3 * sizeof(char *));
	wc[2] = NULL;
	wc[0] = ft_strdup("/usr/bin/wc");
	wc[1] = ft_strdup("-l");
	return (wc);
}

char **cat(void) //! DELeeeeeeeeeeeeTe
{
	char **wc;

	wc = (char **)malloc(4 * sizeof(char *));
	wc[2] = NULL;
	wc[0] = ft_strdup("/bin/cat");
	wc[1] = ft_strdup("-e");
	wc[2] = ft_strdup("123");
	return (wc);
}

char **grep(void) //! DELeeeeeeeeeeeeTe
{
	char **wc;

	wc = (char **)malloc(3 * sizeof(char *));
	wc[2] = NULL;
	wc[0] = ft_strdup("/usr/bin/grep");
	wc[1] = ft_strdup("thar");
	return (wc);
}


t_cmd *new_cmd (int oper) //! DELeeeeeeeeeeeeTe
{
	t_cmd			*el;

	el = (t_cmd *)malloc(sizeof(t_cmd));
	if (!el)
		return (NULL);
	el->util_cmd = NULL;
	el->file = NULL;
	el->next = NULL;
	el->back = NULL;
	if (oper == 1)
		el->argv = cat();
	else if (oper == 2)
		el->argv = grep();
	else if (oper == 3)
		el->argv = wc();
	return (el);
}

void ladd (t_cmd **lst, t_cmd *el) //! DELeeeeeeeeeeeeTe
{
	if (!el)
		return ;
	if (!*lst)
	{
		*lst = el;
		return ;
	}
	el->next = *lst;
	(*lst)->back = el;
	*lst = el;
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

int is_pipes (char *str)
{
	int i;
	int pipess;

	i = 0;
	pipess = 0;
	while (str[i])
		if (str[i++] == '|')
			pipess++;
	return (pipess);
}

void	pipes(t_cmd *cmd, int input, char **env)
{
	// char *grep[] = {"/usr/bin/env", NULL};
	// char *grep[] = {"/bin/cat", "123", NULL};
	// char *wc[] = {"/usr/bin/wc", "-l", NULL};
	// char **inpt;
	int a[2];
	int b[2];
	int flag;
	int len;
	pid_t pid;
(void)input;
	flag = 0;
	len = lenlist(cmd);
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
				execve(cmd->argv[0], cmd->argv, env);
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
			execve(cmd->argv[0], cmd->argv, env);
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
				close(b[0]);//tbbrbrvbrvr
				close(a[1]);
			}
			else
			{
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

void	hardcode (char *input, t_built *built, char **ev, t_env **env)
{
	int pipe;
	t_cmd *cmd = NULL;
	pid_t	pid;

	char *minishell[] = {"/Users/tharodon/Desktop/minishell/Anton/minishell", NULL};
	char *make[] = {"/usr/bin/make", NULL};
	char *makef[] = {"/usr/bin/make", "fclean", NULL};
	int qwer = 0;
		ladd(&cmd, new_cmd(3));
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
		ft_echo(ft_split(input + 4, ' '));
	else if (!ft_strncmp(input, "env", 4))
		ft_env(env);
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
}

int main (int argc, char **argv, char **ev)
{
	t_built *built = NULL;
	t_env *env = NULL;
	(void)argc, (void)argv;
	char *input;
	// pid_t pid;

	// built = (t_built *)malloc(sizeof(t_built));

	env_record(&env, ev);
	// overwrite_env(&env, "OLDPWD=", getcwd(NULL, 0));
	while (1)
	{
		signal(SIGINT, cmd_c);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (input[0])
			hardcode(input, built, ev, &env);
	}
}

	// fd = open("our way",  O_WRONLY | O_TRUNC | O_CREAT, 0666);
	