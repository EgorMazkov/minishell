/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 14:27:09 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/23 14:28:15 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	dollar(t_cmd **cmd, t_env **env)
{
	t_dollar	dollar;
	char		*temp;

	null_dollar(&dollar);
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	torsion_cmd(cmd, &dollar);
	if (!dollar.flag)
		return ;
	if (!ft_strcmp((*cmd)->argv[dollar.i], "$?"))
	{
		temp = (*cmd)->argv[dollar.i];
		(*cmd)->argv[dollar.i] = ft_itoa(g_parms.gexit);
		free(temp);
	}
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
