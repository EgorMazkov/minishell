/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:53 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:19:54 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_argv(char **argv)
{
	int	i;

	i = -1;
	if (argv && *argv != '\0')
	{
		if (*argv)
			while (argv[++i])
				free_str(argv[i]);
	}
	if (argv)
		free(argv);
}

void	free_str(char *string_free)
{
	if (string_free)
		free(string_free);
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*temp;

	while (cmd && *cmd && (*cmd)->back)
		*cmd = (*cmd)->back;
	while (*cmd)
	{
		temp = *cmd;
		*cmd = (*cmd)->next;
		free_argv(temp->argv);
		free_argv(temp->redicts);
		free(temp);
	}
}

void	free_env(t_env **env)
{
	t_env	*temp;

	while (*env && (*env)->back)
		*env = (*env)->back;
	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free_str(temp->variable);
		free_str(temp->value);
		free(temp);
	}
}

void	free_minishell(t_ms *minishell)
{
	free_str(minishell->input);
	free_argv(minishell->env);
	free_argv(minishell->line);
	free_argv(minishell->way);
}
