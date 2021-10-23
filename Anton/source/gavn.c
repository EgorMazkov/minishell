/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gavn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 20:34:00 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/23 17:26:53 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	trim_two(t_cmd **cmd, t_dollar *dollar, t_env **env)
{
	char	*dest;

	dest = (*cmd)->argv[dollar->i];
	(*cmd)->argv[dollar->i] = ft_strtrim((*cmd)->argv[dollar->i], "\"");
	free_str(dest);
	dest = (*cmd)->argv[dollar->i];
	(*cmd)->argv[dollar->i] = ft_strdup(get_variable_env \
	(*env, (*cmd)->argv[dollar->i] + 1));
	free_str(dest);
	dest = (*cmd)->argv[dollar->i];
	(*cmd)->argv[dollar->i] = ft_strjoin("\"", (*cmd)->argv[dollar->i]);
	free_str(dest);
	dest = (*cmd)->argv[dollar->i];
	(*cmd)->argv[dollar->i] = ft_strjoin((*cmd)->argv[dollar->i], "\"");
	free_str(dest);
}

int	check_dollar_null(t_cmd **cmd, t_dollar *dollar, t_env **env)
{
	char	*dest;

	if ((*cmd)->argv[dollar->i][0] == '$' && \
	(*cmd)->argv[dollar->i][1] && (*cmd)->argv[dollar->i][1] != ' ')
	{
		dest = (*cmd)->argv[dollar->i];
		(*cmd)->argv[dollar->i] = ft_strdup(get_variable_env \
		(*env, (*cmd)->argv[dollar->i] + 1));
		free_str(dest);
		return (0);
	}
	return (1);
}

void	check_j(t_cmd **cmd, t_dollar *dollar, t_env **env)
{
	char	*dest;

	if ((*cmd)->argv[dollar->i][dollar->j] == '\"')
	{
		dest = (*cmd)->argv[dollar->i];
		(*cmd)->argv[dollar->i] = ft_strtrim((*cmd)->argv[dollar->i], "\"");
		free_str(dest);
	}
	dest = (*cmd)->argv[dollar->i];
	(*cmd)->argv[dollar->i] = ft_strdup \
	(get_variable_env(*env, (*cmd)->argv[dollar->i] + 1));
	free_str(dest);
	return ;
}

void	torsion_cmd(t_cmd **cmd, t_dollar *dollar)
{
	while ((*cmd)->argv[dollar->i])
	{
		if ((*cmd)->argv[dollar->i][dollar->j] == '$')
		{
			dollar->flag = 1;
			break ;
		}
		else if ((*cmd)->argv[dollar->i][dollar->j] == '\0')
		{
			dollar->i++;
			dollar->j = 0;
			continue ;
		}
		else
			dollar->j++;
	}
}

void	trimmer(t_cmd **cmd, t_dollar *dollar, t_env **env)
{
	while ((*cmd)->argv[dollar->i])
	{
		if (!check_dollar_null(cmd, dollar, env))
			return ;
		dollar->j--;
		if ((*cmd)->argv[dollar->i][dollar->j] == '\"')
		{
			if (dollar->j == 0)
			{
				check_j(cmd, dollar, env);
				return ;
			}
			trim(cmd, dollar);
			trim_two(cmd, dollar, env);
			return ;
		}
		if ((*cmd)->argv[dollar->i][dollar->j] == '\'')
		{
			trim(cmd, dollar);
			break ;
		}
		else
			break ;
	}
}
