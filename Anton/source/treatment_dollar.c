/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:26:36 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/17 17:42:48 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void three_hundred_bucks(t_cmd **cmd, t_env **env)
{
	int i;
	char *temp;
	t_cmd *first_command;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	first_command = *cmd;
	while (*cmd)
	{
		i = -1;
		while ((*cmd)->argv[++i])
		{
			if ((*cmd)->argv[i][0] == '$')
			{
				temp = (*cmd)->argv[i];
				(*cmd)->argv[i] = ft_strdup(get_variable_env(*env, (*cmd)->argv[i] + 1));
				free(temp);
			}
			if ((*cmd)->argv[i][0] == '\'')
				(*cmd)->argv[i] = ft_strtrim((*cmd)->argv[i], "\'");
		}
		*cmd = (*cmd)->next;
	}
	*cmd = first_command;
}
