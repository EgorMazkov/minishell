/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:46 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 18:01:06 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd_no_args(t_env **env, char *temp)
{
	if (!get_variable_env(*env, "HOME"))
	{
		ft_putstr_fd("cd: HOME not set\n", g_parms.fd1_copy);
		return (-1);
	}
	temp = getcwd(NULL, 0);
	overwrite_env(env, "OLDPWD", temp);
	free_str(temp);
	if (chdir(get_variable_env(*env, "HOME")) == -1)
	{
		temp = getcwd(NULL, 0);
		ft_putstr_fd("cd: No such file or directory: HOME", g_parms.fd1_copy);
		ft_putstr_fd("\n", g_parms.fd1_copy);
		overwrite_env(env, "PWD", temp);
		free_str(temp);
		return (-1);
	}
	temp = getcwd(NULL, 0);
	overwrite_env(env, "PWD", temp);
	free_str(temp);
	return (1);
}

int	ft_cd_tild_util(char *arg, t_env **env, char *temp)
{
	temp = ft_strjoin(get_variable_env(*env, "HOME"), ++arg);
	if (chdir(temp) == -1)
	{
		free_str(temp);
		temp = getcwd(NULL, 0);
		overwrite_env(env, "PWD", temp);
		ft_putstr_fd("cd: No such file or directory: ", g_parms.fd1_copy);
		ft_putstr_fd(arg, g_parms.fd1_copy);
		ft_putstr_fd("\n", g_parms.fd1_copy);
		free_str(temp);
		return (-1);
	}
	free_str(temp);
	return (1);
}

int	ft_cd_tild(char *arg, t_env **env, char *temp)
{
	temp = getcwd(NULL, 0);
	if (temp && *temp)
		overwrite_env(env, "OLDPWD", temp);
	free_str(temp);
	if (arg[1] == '\0')
	{
		if (chdir(get_variable_env(*env, "HOME")) == -1)
		{
			ft_putstr_fd("cd: No such file or directory: ", g_parms.fd1_copy);
			ft_putstr_fd(arg, g_parms.fd1_copy);
			ft_putstr_fd("\n", g_parms.fd1_copy);
			return (-1);
		}
	}
	else
	{
		if (ft_cd_tild_util(arg, env, temp) == -1)
			return (-1);
	}
	temp = getcwd(NULL, 0);
	if (temp && *temp)
		overwrite_env(env, "PWD", temp);
	free_str(temp);
	return (1);
}

int	ft_cd(char *arg, t_env **env)
{
	char	*oldpath;
	char	*temp;

	oldpath = NULL;
	temp = NULL;
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
