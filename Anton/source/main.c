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
	char *cat[] = {"/bin/cat", "-e", "123", NULL};
	t_built built;
	(void)argc, (void)argv;
	char *input;
	pid_t pid;

	built.oldpwd = getcwd(NULL, 0);
	while (1)
	{
		signal(SIGINT, jopa);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		if (input[0])
		{
			if (!ft_strncmp(input, "pwd", 4))
				ft_pwd(ev);
			else if (!ft_strncmp(input, "cd", 2))
				ft_cd(input + 3, ev, &built);
			else if (!ft_strncmp(input, "echo ", 5))
				ft_echo(ft_split(input + 4, ' '));
			else if (!ft_strncmp(input, "cat", 3))
			{
				pid = fork();
				if (!pid)
					execve(cat[0], cat, ev);
				wait(NULL);
				write(1, "\n", 1);
			}
		}
	}
}

	// fd = open("our way",  O_WRONLY | O_TRUNC | O_CREAT, 0666);