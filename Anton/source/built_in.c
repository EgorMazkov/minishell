#include "../include/minishell.h"

int    ft_pwd(t_env *env)
{
	t_env *temp;

	temp = env;
	// if (!*env)
	// {
	// 	exit(0);
	// }
	while(temp && temp->back)
		temp = temp->back;
	while (temp)
	{
		if (!ft_strcmp("PWD", temp->variable))
		{
			ft_putstr_fd(temp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		temp = temp->next;
	}
	return (1);
	// printf("%s\n", getenv("PWD"));
}

char *level_down(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	while (s[i] != '/')
		i--;
	s[i] = '\0';
	return (s);
}



char *get_variable_env(t_env *ev, char *str)
{
	while (ev && ev->back)
		ev = ev->back;
	while (ev)
	{
		if (!ft_strcmp(str, ev->variable))
			return (ev->value);
		ev = ev->next;
	}
	return (NULL);
}


int	ft_cd(char *arg, t_env **env)
{
	char *oldpath;
	char *temp;
	/* если pwd || oldpwd удалены, то их надо добавить снова на следующих выходах и входах в директории*/
	if (!arg || !arg[0])
	{
		if (!get_variable_env(*env, "HOME"))
		{
			printf("cd: HOME not set\n");
			return (-1);
		}
		// old->oldpwd = getcwd(NULL, 0);
		temp = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD", temp);
		free_str(temp);
		if (chdir(get_variable_env(*env, "HOME")) == -1)
		{
			temp = getcwd(NULL, 0);
			printf("newerni put\n");
			overwrite_env(env, "PWD", temp);
			free_str(temp);
			return (-1);
		}
		temp = getcwd(NULL, 0);
		overwrite_env(env, "PWD", temp);
		free_str(temp);
	}
	// else if (!ft_strncmp(arg, "..", 3))
	// {
	// 	// old->oldpwd = getcwd(NULL, 0);
	// 	overwrite_env(env, "OLDPWD", getcwd(NULL, 0));
	// 	if (chdir(level_down(getcwd(NULL, 0))) == -1)
	// 		printf("newerni put\n");
	// 	overwrite_env(env, "PWD", getcwd(NULL, 0));
	// }
	else if (!ft_strncmp(arg, "-", 2))
	{
		if (!get_variable_env(*env, "OLDPWD"))
		{
			printf("cd: OLDPWD not set\n");
			return (-1);
		}
		oldpath = getcwd(NULL, 0);
		if (chdir(get_variable_env(*env, "OLDPWD")) == -1)
		{
			overwrite_env(env, "OLDPWD", oldpath);
			free_str(oldpath);
			temp = getcwd(NULL, 0);
			overwrite_env(env, "PWD", temp);
			printf("newerni put\n");
			printf("%s\n", temp);
			free_str(temp);
			return (-1);
		}
		overwrite_env(env, "OLDPWD", oldpath);
		free_str(oldpath);
		temp = getcwd(NULL, 0);
		overwrite_env(env, "PWD", temp);
		printf("%s\n", temp);
		free_str(temp);
	}
	else if (!ft_strncmp(arg, "~", 1))
	{
		// old->oldpwd = getcwd(NULL, 0);
		temp = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD", temp);
		free_str(temp);
		if (arg[1] == '\0')
		{
			if (chdir(getenv("HOME")) == -1)
			{
				printf("newerni put\n");
				return (-1);
			}
		}
		else
		{
			temp = ft_strjoin(getenv("HOME"), ++arg);
			if (chdir(temp) == -1)
			{
				free_str(temp);
				overwrite_env(env, "PWD", getcwd(NULL, 0));
				printf("newerni put\n");
				return (-1);
			}
			free_str(temp);
		}
		temp = getcwd(NULL, 0);
		overwrite_env(env, "PWD", temp);
		free_str(temp);
	}
	else
	{
		// old->oldpwd = getcwd(NULL, 0);
		temp = getcwd(NULL, 0);
		overwrite_env(env, "OLDPWD", temp);
		free_str(temp);
		if (chdir(arg) == -1)
		{
			temp = getcwd(NULL, 0);
			overwrite_env(env, "PWD", temp);
			printf("no such file in directory: %s\n", arg);
			return (-1);
		}
		temp = getcwd(NULL, 0);
		overwrite_env(env, "PWD", temp);
		free_str(temp);
	}
	return (1);
}

int	is_slash_n(char **str)
{
	int	i;
	int ar;

	ar = 0;

	while (str[ar])
	{
		i = 0;
		if (str[ar][i] != '-' || (str[ar][i] == '-' && ft_strlen(str[ar]) == 1))
			return (ar);
		if (str[ar][i] == '-')
		{
			while (str[ar][++i])
				if (str[ar][i] != 'n')
					return (ar);
		}
		else
			return (ar);
		ar++;
	}
	return (ar);
}

void	ft_echo(char **arg)
{
	int str;
	int line;
	int flag_n;

	str = is_slash_n(arg);
	if (str)
		flag_n = 1;
	while (arg[str])
	{
		line = -1;
		while (arg[str][++line])
			write(1, &arg[str][line], 1);
		if (arg[str + 1])
			write(1, " ", 1);
		str++;
	}
	if (!flag_n)
		write(1, "\n", 1);
}

void	ft_env(t_env *ev)
{
	while (ev && ev->back)
		ev = ev->back;
	while (ev)
	{
		if (ev->value && *ev->value)
			printf("%s=%s\n", ev->variable, ev->value);
		ev = ev->next;
	}
}



int args_valid(char *ar)
{
	int str;

	str = 0;
	while (ar[str] && ar[str] != '=')
	{
		if (!ft_isalpha(ar[str]))
			return (0);
		str++;
	}
	return (1);
}




int	export_compare_not_value(t_env **ev, char *s)
{
	int i;
	char *dest;
	char *s1;

	i = -1;
	while (s[++i] && s[i] != '=')
		;
	if (s[i] == '=' && !s[i + 1])
	{
		dest = (char *)malloc(sizeof(char) * 2);
		dest[0] = 127;
		dest[1] = 0;
		while ((*ev)->next)
			*ev = (*ev)->next;
		s1 = ft_strjoin(s, dest);
		env_value_add(ev, new_env_value(s1));
		free(dest);
		free(s1);
		while ((*ev)->back)
			*ev = (*ev)->back;
		alpha_variables(*ev);
		return (1);
	}
	return (0);
}



int	ft_export(t_env **ev, char **arg)
{
	t_env *temp;
	int i;
	int not_valid;
	char *vals;
	char *vars;

	temp = *ev;
	not_valid = 0;
	i = -1;
	if (!arg || !*arg)
	{
		while (temp && temp->back_alpha)
			temp = temp->back_alpha;
		while (temp)
		{
			if (temp->variable && temp->variable[0])
				printf("declare -x %s", temp->variable);
			// if (temp->value[0] == 127)
			// {
			// 	printf("=\"\"\n");
			// 	temp = temp->next_alpha;
			// 	continue ;
			// }
			if (temp->variable && temp->value && *temp->value && !ft_strcmp(temp->value, "\"\""))
				printf("=\"\"\n");
			else if (temp->variable && temp->value && *temp->value)
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
		while (arg[++i])
		{
			if (!args_valid(arg[i]))
			{
				not_valid = 1;
				printf("%s: not a valid identifier\n", arg[i]);
			}
			if (!export_compare_not_value(ev, arg[i]))
			{
				vals = value_of_variable(arg[i]);
				// if (!vals && arg[ft_strlen(arg) - 1] == '=')
				// 	vals = ft_strdup("\"\"");
				vars = name_of_variable(arg[i]);
				if (!overwrite_env(ev, vars, vals))
				{
					while (*ev && (*ev)->next)
						*ev = (*ev)->next;
					env_value_add(ev, new_env_value(arg[i]));
					while ((*ev)->back)
						*ev = (*ev)->back;
					alpha_variables(*ev);
				}
				free(vals);
				free(vars);
			}
		}
	}
	if (not_valid)
		return (-1);
	return (1);
}