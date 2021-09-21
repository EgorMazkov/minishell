#include "../include/minishell.h"

void    ft_pwd(char **env)
{
	if (!*env)
	{
		exit(0);
	}
		printf("%s\n", getcwd(NULL, 0));
	// printf("%s\n", getenv("PWD"));
}

t_cmd *new_cmd (char **cmd, int oper)
{
	t_cmd			*el;

	el = (t_cmd *)malloc(sizeof(t_cmd));
	if (!el)
		return (NULL);
	el->util_cmd = NULL;
	el->argv = ft_envdup(cmd);
	el->file = NULL;
	el->next = NULL;
	el->back = NULL;
	if (oper)
		el->operator = 1;
	else
		el->operator = 0;
	return (el);
}

void ladd (t_cmd **lst, t_cmd *el)
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

char *level_down(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	while (s[i] != '/')
		i--;
	s[i] = '\0';
	return (s);
}

void	ft_cd(char *arg, char **env, t_built *old)
{
	char *oldpath;
	(void)env;

	if (!arg || !arg[0])
	{
		old->oldpwd = getcwd(NULL, 0);
		chdir(getenv("HOME"));
	}
	else if (!ft_strncmp(arg, "..", 3))
	{
		old->oldpwd = getcwd(NULL, 0);
		chdir(level_down(getcwd(NULL, 0)));
	}
	else if (!ft_strncmp(arg, "-", 2))
	{
		oldpath = old->oldpwd;
		old->oldpwd = getcwd(NULL, 0);
		chdir(oldpath);
	}
	else if (!ft_strncmp(arg, "~", 1))
	{
		old->oldpwd = getcwd(NULL, 0);
		if (arg[1] == '\0')
			chdir(getenv("HOME"));
		else
			chdir(ft_strjoin(getenv("HOME"), ++arg));
	}
	else
		chdir(arg);
		/*
		необходимо допилить: изменение путия в env;
		*/
}

void	ft_echo(char **arg)
{
	int str;
	int line;

	str = -1;
	while (arg[++str])
	{
		line = -1;
		while (arg[str][++line])
			write(1, &arg[str][line], 1);
		write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void	ft_env(t_built *ev)
{
	int i;

	i = 0;
	while (ev->env[++i])
		printf("%s\n", ev->env[i]);
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
	char *grep[] = {"/bin/cat", "123", NULL};
	char *wc[] = {"/usr/bin/wc", "-l", NULL};
	// char **inpt;
	int a[2];
	int b[2];
	int flag;
	pid_t pid;
(void)input;
	flag = 0;

	// pipe(a);
	// pid = fork();
	// if (!pid)
	// {
	// 	close(a[0]);
	// 	dup2(a[1], 1);
	// 	close(a[1]);
	// 	execve(cat[0], cat, env);
	// }
	// else
	// {
	// 	close(a[1]);
	// 	pid = fork();
	// 	if (!pid)
	// 	{
	// 		dup2(a[0], 0);
	// 		close(a[0]);
	// 		execve(wc[0], wc, env);
	// 	}
	// }
	// int iq = 0;
	// while (iq++ < 2)
	// 	wait(0);
	// return ;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
		if (!pid)
		{
			if (!cmd->next)
			{
				if (!flag)
					dup2(b[0], 0);
				else
					dup2(a[0], 0);
				execve(wc[0], wc, env);
			}
			if (!flag && !cmd->back)
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
				close(b[0]);
				dup2(b[1], 1);
			}
				execve(grep[0], grep, env);
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
				close(a[1]);
			else
				close(b[1]);
			if (!flag)
				flag = 1;
			else
				flag = 0;
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
	while(i < 3)
	{
		wait(0);
		i++;
	}
}

void	hardcode (char *input, t_built *built, char **ev)
{
	char *cat[] = {"/bin/cat", "-e", "123", NULL};
	char *grep[] = {"/usr/bin/grep", "a", NULL};
	char *wc[] = {"/usr/bin/wc", "-l", NULL};
	pid_t pid;
	int pipe;
	t_cmd *cmd = NULL;

	ladd(&cmd, new_cmd(wc, 0));
	ladd(&cmd, new_cmd(grep, 1));
	ladd(&cmd, new_cmd(cat, 1));

	while (cmd->back)
		cmd = cmd->back;

	if (is_pipes(input))
	{
		pipe = is_pipes(input);
		pipes(cmd, 0, ev);
		return ;
	}
	if (!ft_strncmp(input, "pwd", 4))
		ft_pwd(ev);
	else if (!ft_strncmp(input, "cd", 2))
		ft_cd(input + 3, ev, built);
	else if (!ft_strncmp(input, "echo ", 5))
		ft_echo(ft_split(input + 4, ' '));
	else if (!ft_strncmp(input, "env", 4))
		ft_env(built);
	else if (!ft_strncmp(input, "cat", 3))
	{
		pid = fork();
		if (!pid)
			execve(cat[0], cat, ev);
		wait(NULL);
		write(1, "\n", 1);
	}
	else
		printf("command not found: %s\n", input);
}

int main (int argc, char **argv, char **ev)
{
	t_built built;
	(void)argc, (void)argv;
	char *input;
	// pid_t pid;
	while (1)
	{
		signal(SIGINT, cmd_c);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		built.env = ft_envdup(ev);
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (input[0])
			hardcode(input, &built, ev);
	}
}

	// fd = open("our way",  O_WRONLY | O_TRUNC | O_CREAT, 0666);