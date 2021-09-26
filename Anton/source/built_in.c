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

char *get_old_path_to_env(t_env *ev)
{
	while (ev->back)
		ev = ev->back;
	while (ev)
	{
		if (!ft_strncmp("OLDPWD=", ev->variable, 7))
			return (ev->value);
		ev = ev->next;
	}
	return (NULL);
}

void	ft_cd(char *arg, t_env **env, t_built *old)
{
	char *oldpath;

	if (!arg || !arg[0])
	{
		old->oldpwd = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD=", getcwd(NULL, 0));
		if (chdir(getenv("HOME")) == -1)
			printf("newerni put\n");
		overwrite_env(env, "PWD=", getcwd(NULL, 0));
	}
	else if (!ft_strncmp(arg, "..", 3))
	{
		old->oldpwd = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD=", getcwd(NULL, 0));
			if (chdir(level_down(getcwd(NULL, 0))) == -1)
				printf("newerni put\n");
		overwrite_env(env, "PWD=", getcwd(NULL, 0));
	}
	else if (!ft_strncmp(arg, "-", 2))
	{
		if (!get_old_path_to_env(*env))
		{
			printf("cd: OLDPWD not set\n");
			return ;
		}
		oldpath = get_old_path_to_env(*env);
		if (!oldpath)
			oldpath = old->oldpwd;
		old->oldpwd = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD=", getcwd(NULL, 0));
		if (chdir(oldpath) == -1)
			printf("newerni put\n");
		overwrite_env(env, "PWD=", getcwd(NULL, 0));
		printf("%s\n", getcwd(NULL, 0));
	}
	else if (!ft_strncmp(arg, "~", 1))
	{
		old->oldpwd = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD=", getcwd(NULL, 0));
		if (arg[1] == '\0')
		{
			if (chdir(getenv("HOME")) == -1)
				printf("newerni put\n");
		}
		else
			if (chdir(ft_strjoin(getenv("HOME"), ++arg)) == -1)
				printf("newerni put\n");
		overwrite_env(env, "PWD=", getcwd(NULL, 0));
	}
	else
	{
		old->oldpwd = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD=", getcwd(NULL, 0));
		if (chdir(arg) == -1)
			printf("no such file in directory: %s\n", arg);
		overwrite_env(env, "PWD=", getcwd(NULL, 0));
	}
}

int	is_slash_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-' || (str[i] == '-' && ft_strlen(str) == 1))
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
	while (arg[++str])
	{
		if (!is_slash_n(arg[str]))
		{
			line = -1;
			while (arg[str][++line])
				write(1, &arg[str][line], 1);
			if (arg[str + 1])
				write(1, " ", 1);
		}
	}
	if (!is_slash_n(arg[0]))
		write(1, "\n", 1);
}

void	ft_env(t_env **ev)
{
	while ((*ev)->back)
		*ev = (*ev)->back;
	while (*ev)
	{
		printf("%s%s\n", (*ev)->variable, (*ev)->value);
		*ev = (*ev)->next;
		if (!(*ev)->next)
			break ;
	}
}