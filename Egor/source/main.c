/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:16:23 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/30 16:14:37 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
echo "123 123 123 123 123 123 1"
*/

int	main(int argc, char **argv, char **ev)
{
	t_ms	*minishell;
	t_cmd	*cmd;
	(void)argc;
	(void)argv;

	minishell = NULL;
	cmd = NULL;
	minishell = (t_ms *)malloc(sizeof(t_ms));
	null_struct(minishell, ev);
	while (1)
	{
		minishell->input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		if (minishell->input[0])
			minishell->line = ft_split_for_minishell(minishell->input, ' ');
		if (!minishell->line)
			continue;
		record_cmd(&cmd, minishell);
	}
}

void	record_cmd(t_cmd **cmd, t_ms *minishell)
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
				break ;
			}
			i++;
		}
		if (!*minishell->line)
			break ;
		i = 0;
	}
	// int q;
	// while ((*cmd)->back)
	// 	*cmd = (*cmd)->back;
	// while (*cmd)
	// {
	// 	q = -1;
	// 	while ((*cmd)->argv[++q])
	// 		printf("%s\n", (*cmd)->argv[q]);
	// 	*cmd = (*cmd)->next;
	// }
}

t_cmd *new_cmd(t_ms *minishell) //! DELeeeeeeeeeeeeTe
{
	t_cmd			*el;

	int	j;
	
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


	int qw = -1;
	while (el->argv[++qw])
		printf("%s\n", el->argv[qw]);

	return (el);
}

int		check_bin(t_ms *minishell)
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
	return  (0);
}


int len_tab(char **str)
{
	int i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

char **jopa(t_ms *minishell, int i)
{
	char **dest;
	int str = 0;

	dest = malloc(sizeof(char *) * len_tab(minishell->line + i + 1) + 1);
	i++;
	while (minishell->line[i] != '\0')
	{
		dest[str++] = ft_strdup(minishell->line[i]);
		i++;
	}
	dest[str] = NULL;
	return (dest);
}

char **record_cmd2(t_ms *minishell)
{
	int	i;
	char **dest;

	i = 0;
	while (*minishell->line[i] != '|' && minishell->line[i])
		i++;
	dest = (char **)malloc(sizeof(char *) * i);
	i = 0;
	minishell->line[0] = check_path(minishell);
	while (*minishell->line[i] != '|' && minishell->line[i])
	{
		dest[i] = ft_strdup(minishell->line[i]);
		i++;
	}
	dest[i] = NULL;
	minishell->line = jopa(minishell, i);
	return (dest);
}

void lst_add (t_cmd **lst, t_cmd *el) //! DELeeeeeeeeeeeeTe
{
	if (!el)
		return ;
	if (!*lst)
	{
		*lst = el;
		return ;
	}
	el->next = *lst;
	(*lst)->back = el;
	*lst = el;
}


char *check_path(t_ms *minishell)
{
	char *way;
	int	check;

	check = check_bin(minishell);
	if (check)
		return (minishell->line[0]);
	else
	{
		get_path(minishell);
		way = right_way(minishell);
		return (way);
	}
	return (0);
}