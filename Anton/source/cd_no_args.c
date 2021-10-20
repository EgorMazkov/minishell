#include "../include/minishell.h"

int ft_cd_home(t_env **env, char *oldpath, char *temp)
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
	return (1);
}

int ft_cd_no_parse(char *arg, t_env **env, char *temp)
{
	// old->oldpwd = getcwd(NULL, 0) 
	temp = getcwd(NULL, 0);
	overwrite_env(env, "OLDPWD", temp);
	free_str(temp);
	if (chdir(arg) == -1)
	{
		temp = getcwd(NULL, 0);
		overwrite_env(env, "PWD", temp);
		printf("no such file in directory: %s\n", arg);
		free_str(temp);
		return (-1);
	}
	temp = getcwd(NULL, 0);
	overwrite_env(env, "PWD", temp);
	free_str(temp);
	return (1);
}