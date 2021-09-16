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

typedef struct s_built
{
	char *oldpwd;
} t_built;

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

void	ft_echo(char *arg)
{
	int i;

	i = 0;
	if (!ft_strncmp(arg, "-n", 2))
	{
		while (arg[++i]== 'n')
			;
		i++;
	}
	while (arg[i])
		write(1, &arg[i++], 1);
	if (ft_strncmp(arg, "-n", 2))
		write(1, "\n", 1);
	/*
	можно сделать двойным массивом аргументы
	*/
}

void	jopa(int signum)
{
	(void)signum;
	// g_param->ret = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


int main (int argc, char **argv, char **ev)
{
	// int fd_output;
	int fd1;
	char *cat[] = {"/bin/cat", NULL};
	t_built built;
	(void)argc, (void)argv;
	char *input;

	built.oldpwd = getcwd(NULL, 0);
	while (1)
	{
		signal(SIGINT, jopa);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		if (input[0])
		{
			if (!ft_strncmp(input, "pwd", 4))
				ft_pwd(ev);
			else if (!ft_strncmp(input, "cd", 2))
				ft_cd(input + 3, ev, &built);
			else if (!ft_strncmp(input, "cat", 3))
			{
				fd1 = open("123",  O_WRONLY | O_TRUNC | O_CREAT, 0666);
				execve(cat[0], cat, ev);
			}
		}
	}
}

	// fd = open("our way",  O_WRONLY | O_TRUNC | O_CREAT, 0666);