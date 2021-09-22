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

void	ft_cd(char *arg, char **env, t_built *old)
{
	char *oldpath;
	(void)env;

	if (!arg || !arg[0])
	{
		old->oldpwd = getcwd(NULL, 0);
		if (chdir(getenv("HOME")) == -1)
			printf("newerni put\n");
	}
	else if (!ft_strncmp(arg, "..", 3))
	{
		old->oldpwd = getcwd(NULL, 0);
			if (chdir(level_down(getcwd(NULL, 0))) == -1)
				printf("newerni put\n");
	}
	else if (!ft_strncmp(arg, "-", 2))
	{
		oldpath = old->oldpwd;
		old->oldpwd = getcwd(NULL, 0);
		if (chdir(oldpath) == -1)
			printf("newerni put\n");
	}
	else if (!ft_strncmp(arg, "~", 1))
	{
		old->oldpwd = getcwd(NULL, 0);
		if (arg[1] == '\0')
		{
			if (chdir(getenv("HOME")) == -1)
				printf("newerni put\n");
		}
		else
			if (chdir(ft_strjoin(getenv("HOME"), ++arg)) == -1)
				printf("newerni put\n");
	}
	else
		if (chdir(arg) == -1)
			printf("no such file in directory: %s\n", arg);
		/*
		необходимо допилить: изменение путия в env;
		*/
}

int	is_slash_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	if (str[i] == '-')
		while (str[++i])
			if (str[i] != 'n')
				return (0);
	return (1);
}

void	ft_echo(char **arg)
{
	int str;
	int line;

	str = -1;
	if (is_slash_n(arg[0]))
		str++;
	while (arg[++str])
	{
		line = -1;
		while (arg[str][++line])
			write(1, &arg[str][line], 1);
		if (arg[str + 1])
			write(1, " ", 1);
	}
	if (!is_slash_n(arg[0]))
		write(1, "\n", 1);
}

void	ft_env(t_env *ev)
{
	while (ev->back)
		ev = ev->back;
	while (ev)
	{
		printf("%s\n", ev->value);
		ev = ev->next;
	}
}