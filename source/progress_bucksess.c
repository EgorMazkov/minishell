/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bucksess.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:20:00 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:20:01 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	bucksonly(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] != '$')
			return (0);
	return (1);
}

void	three_hundred_bucks_util(t_cmd **cmd, int i)
{
	char	*temp;

	if ((*cmd)->argv[i] && (*cmd)->argv[i][0] == '\'')
	{
		temp = (*cmd)->argv[i];
		(*cmd)->argv[i] = ft_strtrim((*cmd)->argv[i], "\'");
		free_str(temp);
	}
	else if ((*cmd)->argv[i] && (*cmd)->argv[i][0] == '\"')
	{
		temp = (*cmd)->argv[i];
		(*cmd)->argv[i] = ft_strtrim((*cmd)->argv[i], "\"");
		free_str(temp);
	}
}

void	bucks(t_cmd **cmd, t_env **env)
{
	char	*temp;
	int		i;

	i = -1;
	while ((*cmd)->argv[++i])
	{
		three_hundred_bucks_util(cmd, i);
		if (!ft_strcmp((*cmd)->argv[i], "$?"))
		{
			temp = (*cmd)->argv[i];
			(*cmd)->argv[i] = ft_itoa(g_parms.gexit);
			free(temp);
			continue ;
		}
		if ((*cmd)->argv[i][0] == '$')
		{
			temp = (*cmd)->argv[i];
			if (bucksonly(temp))
				break ;
			(*cmd)->argv[i] = ft_strdup(get_variable_env(*env, \
			(*cmd)->argv[i] + 1));
			free(temp);
		}
	}
}

void	three_hundred_bucks(t_cmd **cmd, t_env **env)
{
	int			i;
	t_cmd		*first_command;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	first_command = *cmd;
	while (*cmd)
	{
		i = -1;
		if (!(*cmd)->argv || !(*cmd)->argv[0])
		{
			*cmd = (*cmd)->next;
			continue ;
		}
		bucks(cmd, env);
		*cmd = (*cmd)->next;
	}
	*cmd = first_command;
}
