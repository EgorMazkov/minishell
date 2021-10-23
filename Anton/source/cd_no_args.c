/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_no_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:47 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 17:57:43 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_cd_home(t_env **env, char *oldpath, char *temp)
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
		ft_putstr_fd(temp, g_parms.fd1_copy);
		ft_putstr_fd("\n", g_parms.fd1_copy);
		free_str(temp);
		return (-1);
	}
	overwrite_env(env, "OLDPWD", oldpath);
	free_str(oldpath);
	temp = getcwd(NULL, 0);
	overwrite_env(env, "PWD", temp);
	ft_putstr_fd(temp, g_parms.fd1_copy);
	ft_putstr_fd("\n", g_parms.fd1_copy);
	free_str(temp);
	return (1);
}

int	ft_cd_no_parse(char *arg, t_env **env, char *temp)
{
	temp = getcwd(NULL, 0);
	if (temp && *temp)
		overwrite_env(env, "OLDPWD", temp);
	free_str(temp);
	if (chdir(arg) == -1)
	{
		temp = getcwd(NULL, 0);
		overwrite_env(env, "PWD", temp);
		ft_putstr_fd("cd: No such file or directory: ", g_parms.fd1_copy);
		ft_putstr_fd(arg, g_parms.fd1_copy);
		ft_putstr_fd("\n", g_parms.fd1_copy);
		free_str(temp);
		return (-1);
	}
	temp = getcwd(NULL, 0);
	if (temp && *temp)
		overwrite_env(env, "PWD", temp);
	free_str(temp);
	return (1);
}
