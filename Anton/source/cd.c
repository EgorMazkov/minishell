#include "../include/minishell.h"

int ft_cd_no_args(t_env **env, char *temp)
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
	return (1);
}

int ft_cd_tild_util(char *arg, t_env **env, char *temp)
{
	temp = ft_strjoin(get_variable_env(*env, "HOME"), ++arg);
	if (chdir(temp) == -1)
	{
		free_str(temp);
		temp = getcwd(NULL, 0);
		overwrite_env(env, "PWD", temp);
		printf("newerni put\n");
		free_str(temp);
		return (-1);
	}
	free_str(temp);
	return (1);
}

int ft_cd_tild(char *arg, t_env **env, char *temp)
{
	// old->oldpwd = getcwd(NULL, 0);
	temp = getcwd(NULL, 0);
	overwrite_env(env, "OLDPWD", temp);
	free_str(temp);
	if (arg[1] == '\0')
	{
		if (chdir(get_variable_env(*env, "HOME")) == -1)
		{
			printf("newerni put\n");
			printf("no such file in directory: %s\n", arg);
			return (-1);
		}
	}
	else
	{
		if (ft_cd_tild_util(arg, env, temp) == -1)
			return (-1);
	}
	temp = getcwd(NULL, 0);
	overwrite_env(env, "PWD", temp);
	free_str(temp);
	return (1);
}



int ft_cd(char *arg, t_env **env)
{
	char *oldpath;
	char *temp;

	oldpath = NULL;
	temp = NULL;
	/* если pwd || oldpwd удалены, то их надо добавить снова на следующих выходах и входах в директории*/
	if (!arg || !arg[0])
		return (ft_cd_no_args(env, temp));
	else if (!ft_strncmp(arg, "-", 2))
		return (ft_cd_home(env, oldpath, temp));
	else if (!ft_strncmp(arg, "~", 1))
		return (ft_cd_tild(arg, env, temp));
	else
		return (ft_cd_no_parse(arg, env, temp));
	return (1);
}