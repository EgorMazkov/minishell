/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:27:09 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/23 23:58:04 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	check_echo_qoute(t_cmd **cmd, t_dollar *dollar)
{
	int		j;
	char	*dest;

	j = 0;
	dollar->i = 0;
	if ((*cmd)->argv[dollar->i])
	{
		while ((*cmd)->argv[dollar->i] && (*cmd)->argv[dollar->i][j] != '\"')
		{
			if ((*cmd)->argv[dollar->i][j] == '\0')
			{
				j = 0;
				dollar->i++;
				continue ;
			}
			j++;
		}
		if ((*cmd)->argv[dollar->i] && (*cmd)->argv[dollar->i][j] == '\"')
		{
			dest = (*cmd)->argv[dollar->i];
			(*cmd)->argv[dollar->i] = ft_strtrim((*cmd)->argv[dollar->i], "\"");
			free(dest);
			return ;
		}
	}
}

void	dollar_exit(t_cmd **cmd)
{
	int		i;
	t_cmd	*first;
	char	*temp;

	i = -1;
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	first = *cmd;
	while (*cmd)
	{
		while ((*cmd)->argv[++i])
		{
			if (!ft_strcmp((*cmd)->argv[i], "$?"))
			{
				temp = (*cmd)->argv[i];
				(*cmd)->argv[i] = ft_itoa(g_parms.gexit);
				free(temp);
			}
		}
		*cmd = (*cmd)->next;
	}
	*cmd = first;
}

void	dollar(t_cmd **cmd, t_env **env)
{
	t_dollar	dollar;

	null_dollar(&dollar);
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	torsion_cmd(cmd, &dollar);
	check_echo_qoute(cmd, &dollar);
	if (!dollar.flag)
		return ;
	dollar_exit(cmd);
	trimmer(cmd, &dollar, env);
}

void	exec(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	int	built_ex;

	g_parms.fd0_copy = dup(0);
	g_parms.fd1_copy = dup(1);
	if (parser_and_validator(cmd, minishell, env))
	{
		swapping_fd(g_parms.fd0_copy, g_parms.fd1_copy);
		return ;
	}
	if (!(*cmd)->next && !(*cmd)->back)
		built_ex = built_in_run(*cmd, env);
	if ((*cmd)->next || (*cmd)->back)
	{
		pipes(*cmd, env);
		warning_exit();
	}
	else if (built_ex == -1)
		g_parms.gexit = 1;
	else if (built_ex == 1)
		g_parms.gexit = 0;
	else if (!*cmd || !(*cmd)->argv || !*(*cmd)->argv)
		return ;
	else if (*(*cmd)->argv && !is_builtin(*(*cmd)->argv))
		run_bash_command_from_exec(cmd, env);
	swapping_fd(g_parms.fd0_copy, g_parms.fd1_copy);
}
