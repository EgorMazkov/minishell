/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ghumbert_for_two.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:57:22 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/10 20:25:16 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_bin(t_ms *minishell)
{
	int	i;

	i = 0;
	if (minishell->line)
	{
		if (!ft_strncmp(minishell->line[i], "cd", 2))
			return (1);
		if (!ft_strncmp(minishell->line[i], "env", 3))
			return (1);
		if (!ft_strncmp(minishell->line[i], "echo", 4))
			return (1);
		if (!ft_strncmp(minishell->line[i], "pwd", 3))
			return (1);
		if (!ft_strncmp(minishell->line[i], "unset", 5))
			return (1);
		if (!ft_strncmp(minishell->line[i], "exit", 4))
			return (1);
		if (!ft_strncmp(minishell->line[i], "export", 6))
			return (1);
	}
	return (0);
}

void	record_cmd_pipe(t_cmd **cmd, t_ms *minishell)
{
	int	i;

	i = 0;
	while (minishell->line[i])
	{
		while (minishell->line[i])
		{
			if (*minishell->line[i] == '|')
			{
				lst_add(cmd, new_cmd(minishell));
				i = 0;
				break ;
			}
			i++;
		}
	}
	lst_add(cmd, new_cmd(minishell));
}

void	record_rdct(t_rdct **rdct, t_ms *minishell, t_cmd *cmd)
{
	int	i;

	i = 0;
	(void)cmd;
	while (minishell->line[i])
	{
		while (minishell->line[i])
		{
			if (minishell->line[i] && 
		((*minishell->line[i] == '>' && minishell->line[i][1] != '>') || 
		(*minishell->line[i] == '<'  && minishell->line[i][1] != '<') ||
		(*minishell->line[i] == '>' && minishell->line[i][1] == '>') || 
		(*minishell->line[i] == '<' && minishell->line[i][1] == '<')))
			{
				lstadd_rdct(rdct, new_rcdt(minishell));
				lstadd_rdct(&cmd->rdct, *rdct);
				i = 0;
				break ;
			}
			i++;
		}
	}
	// lstadd_rdct(&rdct, new_rcdt(minishell));
}

char	**write_rdct(t_ms *minishell, int i)
{
	int	j;
	int	x;
	int	y;
	static int a;

	j = 0;
	x = 0;
	y = 0;
	char **dest;
	dest = NULL;
	while (j != i)
	{
		// dest[a][x] = ;//запись посимвольно
		j++;
	}
	printf("%d\n", a);
	a++;
	x = 0;
	if ((minishell->line[x][j] == '>' && minishell->line[x][j + 1] != '>') || 
		(minishell->line[x][j] == '<'  && minishell->line[x][j + 1] != '<'))
	{
			printf(">\n");
		// dest[a][x] = ;//запись посимвольно
	}
	else if ((minishell->line[x][j] == '>' && minishell->line[x][j + 1] == '>') || 
		(minishell->line[x][j] == '<' && minishell->line[x][j + 1] == '<'))
	{
		while (j != 2)
		{
			printf(">>\n");
			// dest[a][x] = ;//запись посимвольно
			j++;
		}
	}
	a++;
	while (minishell->line[x][j] != ' ' || minishell->line[x][j] != '\0')
	{
		printf("0\n");
		j++;
		// dest[a][x] = ;
	}
	a = 0;
	j = 0;
	return (0);
}

void	record_rdct_together(t_ms *minishell, t_rdct **rdct)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (minishell->line[i][j])
	{
		if ((minishell->line[i][j] == '>' && minishell->line[i][j + 1] != '>') || 
		(minishell->line[i][j] == '<'  && minishell->line[i][j + 1] != '<') ||
		(minishell->line[i][j] == '>' && minishell->line[i][j + 1] == '>') || 
		(minishell->line[i][j] == '<' && minishell->line[i][j + 1] == '<'))
		{
			minishell->line = write_rdct(minishell, j);
			lstadd_rdct(rdct, new_rcdt(minishell));
		}
		j++;
	}
}

void	record_cmd(t_cmd **cmd, t_ms *minishell, t_env **env, t_rdct **rdct)
{
	int	i;
	int	check_pipe;
	int	check_rc;
	int	j;

	(void)env;
	(void)rdct;

	check_rc = 0;
	i = 0;
	j = 0;
	check_pipe = 0;
	while (minishell->line[i][j] && minishell->line[i][j] != ' ' && minishell->line[i])
	{
		if ((minishell->line[i][j] == '>' && minishell->line[i][j + 1] != '>') || 
		(minishell->line[i][j] == '<'  && minishell->line[i][j + 1] != '<') ||
		(minishell->line[i][j] == '>' && minishell->line[i][j + 1] == '>') || 
		(minishell->line[i][j] == '<' && minishell->line[i][j + 1] == '<'))
			record_rdct_together(minishell, rdct);
		else if (minishell->line[i][j] == ' ')
			break ;
		j++;
	}
	while (minishell->line[i])
	{
		if (*minishell->line == NULL)
			break ;
		if (*minishell->line[i] == '|')
		{
			check_pipe = 1;
			record_cmd_pipe(cmd, minishell);
			// break ;
			i = 0;
		}
		if (minishell->line[i] && 
		((*minishell->line[i] == '>' && minishell->line[i][1] != '>') || 
		(*minishell->line[i] == '<'  && minishell->line[i][1] != '<') ||
		(*minishell->line[i] == '>' && minishell->line[i][1] == '>') || 
		(*minishell->line[i] == '<' && minishell->line[i][1] == '<')))
		{
			check_rc = 1;
			lst_add(cmd, new_cmd(minishell));
			record_rdct(rdct, minishell, *cmd);
		}
		i++;
		// if (check_pipe || check_rc)
		// 	break ;
	}
	if (!check_pipe && !check_rc)
		lst_add(cmd, new_cmd(minishell));
}

t_cmd	*new_cmd(t_ms *minishell)
{
	t_cmd	*el;
	int		j;

	j = 0;
	el = (t_cmd *)malloc(sizeof(t_cmd));
	if (!el)
		return (NULL);
	el->util_cmd = NULL;
	el->file = NULL;
	el->next = NULL;
	el->back = NULL;
	el->operator = -999;
	el->argv = record_cmd2(minishell);
	return (el);
}
