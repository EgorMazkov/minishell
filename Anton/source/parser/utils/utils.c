/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:27:08 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/20 16:28:37 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_next_cmd(t_cmd **cmd)
{
	if ((*cmd)->next)
	{
		*cmd = (*cmd)->next;
		return (1);
	}
	else
		return (0);
}

t_ms	*null_struct(void)
{
	t_ms *minishell;

	minishell = (t_ms *)malloc(sizeof(t_ms));
	minishell->input = NULL;
	minishell->line = NULL;
	minishell->env = NULL;
	minishell->way = NULL;
	return (minishell);
}

int	len_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	record_list_cmd(char *dest, char *line, t_cmd **cmd)
{
	if (line && *line)
	{
		dest = (*cmd)->argv[0];
		(*cmd)->argv[0] = ft_strdup(line);
		free(dest);
		free(line);
	}
}

t_cmd	*new_cmd(t_ms *minishell)
{
	t_cmd	*el;
	int		j;

	j = 0;
	el = (t_cmd *)malloc(sizeof(t_cmd));
	if (!el)
		return (NULL);
	el->fd_her = -1;
	el->fd_read = -1;
	el->fd_write = -1;
	el->next = NULL;
	el->back = NULL;
	el->redicts = NULL;
	el->argv = record_cmd2(minishell);
	return (el);
}

void	dollar(t_cmd **cmd, t_env **env)
{
	t_dollar dollar;
	char *temp;

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
