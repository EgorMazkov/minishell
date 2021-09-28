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
		if (!ft_strcmp("OLDPWD", ev->variable))
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
		overwrite_env(env, "OLDPWD", getcwd(NULL, 0));
		if (chdir(getenv("HOME")) == -1)
			printf("newerni put\n");
		overwrite_env(env, "PWD", getcwd(NULL, 0));
	}
	else if (!ft_strncmp(arg, "..", 3))
	{
		old->oldpwd = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD", getcwd(NULL, 0));
		if (chdir(level_down(getcwd(NULL, 0))) == -1)
			printf("newerni put\n");
		overwrite_env(env, "PWD", getcwd(NULL, 0));
	}
	else if (!ft_strncmp(arg, "-", 2))
	{
		if (!get_old_path_to_env(*env))
		{
			printf("cd: OLDPWD not set\n");
			return ;
		}
		oldpath = getcwd(NULL, 0);
		if (chdir(get_old_path_to_env(*env)) == -1)
			printf("newerni put\n");
		overwrite_env(env, "OLDPWD", oldpath);
		overwrite_env(env, "PWD", getcwd(NULL, 0));
		printf("%s\n", getcwd(NULL, 0));
	}
	else if (!ft_strncmp(arg, "~", 1))
	{
		old->oldpwd = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD", getcwd(NULL, 0));
		if (arg[1] == '\0')
		{
			if (chdir(getenv("HOME")) == -1)
				printf("newerni put\n");
		}
		else
			if (chdir(ft_strjoin(getenv("HOME"), ++arg)) == -1)
				printf("newerni put\n");
		overwrite_env(env, "PWD", getcwd(NULL, 0));
	}
	else
	{
		old->oldpwd = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD", getcwd(NULL, 0));
		if (chdir(arg) == -1)
			printf("no such file in directory: %s\n", arg);
		overwrite_env(env, "PWD", getcwd(NULL, 0));
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

void	ft_env(t_env *ev)
{
	while (ev->back)
		ev = ev->back;
	while (ev)
	{
		if (ev->value)
			printf("%s=%s\n", ev->variable, ev->value);
		ev = ev->next;
	}
}
void	ft_export(t_env **ev, char *arg)
{
	t_env *temp;
	char *vals;
	char *vars;

	temp = *ev;
	if (!arg)
	{
		while (temp->back_alpha)
			temp = temp->back_alpha;
		while (temp)
		{
			if (temp->variable && temp->variable[0])
				printf("declare -x %s", temp->variable);
			if (temp->variable && temp->value && !ft_strcmp(temp->value, "\"\""))
				printf("=\"\"\n");
			else if (temp->variable && temp->value)
				printf("=\"%s\"\n", temp->value);
			else
				printf("\n");
			temp = temp->next_alpha;
		}
		// temp = get_maxmin_variable(*ev, MIN, 1);
		// while (temp)
		// {
		// 	printf("%s%s\n", temp->variable, temp->value);
		// 	temp = temp->next_alpha;
		// }
	}
	else
	{
		vals = value_of_variable(arg);
		// if (!vals && arg[ft_strlen(arg) - 1] == '=')
		// 	vals = ft_strdup("\"\"");
		vars = name_of_variable(arg);
		if (!overwrite_env(ev, vars, vals))
		{
			while ((*ev)->next)
				*ev = (*ev)->next;
			env_value_add(ev, new_env_value(arg));
			while ((*ev)->back)
				*ev = (*ev)->back;
			alpha_variables(*ev);
		}
		free(vals);
		free(vars);
	}
}