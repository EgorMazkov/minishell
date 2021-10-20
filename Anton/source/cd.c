#include "../include/minishell.h"




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