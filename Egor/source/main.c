/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:16:23 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/03 15:33:49 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
echo "123 123 123 123 123 123 1"
*/
static void	null_minishell(t_ms *minishell)
{
	free(minishell);
}

void test(t_cmd **cmd)
{
	t_cmd *temp;
	int i = -1;
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (temp)
	{
		while (temp->argv[++i])
			printf("%s\n", temp->argv[i]);
		printf("----------------((Anton))------------------\n");
		temp = temp->next;
		i = -1;
		
	}
}

int	main(int argc, char **argv, char **ev)
{
	t_ms	*minishell;
	t_cmd	*cmd;
	(void)argc;
	(void)argv;

	minishell = NULL;
	cmd = NULL;
	while (1)
	{
		minishell = (t_ms *)malloc(sizeof(t_ms));
		null_struct(minishell, ev);
		minishell->input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		if (minishell->input[0])
			minishell->line = ft_split_for_minishell(minishell->input, ' ');
		// int i = 0;
		// while (minishell->line[i])
		// {
		// 	printf("%s\n", minishell->line[i]);
		// 	i++;
		// }
		if (!minishell->line)
			continue;
		record_cmd(&cmd, minishell);
		test(&cmd);
		null_minishell(minishell);
	}
}

void	record_cmd_pipe(t_cmd **cmd, t_ms *minishell)
{
	int	i;

	// i = 0;
	// while (minishell->line[i])
	// {
	// 	printf("%s\n", minishell->line[i]);
	// 	i++;
	// }
	i = 0;
	// while (1); // теряет всю строку после того как была написана команда echo "1 2 3"
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
		// printf("123 : %s\n", minishell->line[i]);
		}
	}
	lst_add(cmd, new_cmd(minishell));
}

void	record_cmd(t_cmd **cmd, t_ms *minishell)
{
	int	i;
	int	check_pipe;
	
	i = 0;
	check_pipe = 0;
	while (minishell->line[i])
	{
		if (*minishell->line[i] == '|')
		{
			check_pipe = 1;
			record_cmd_pipe(cmd, minishell);
			break ;
		}
		i++;
	}
	if (check_pipe == 0)
		lst_add(cmd, new_cmd(minishell));
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


	// int qw = -1;
	// while (el->argv[++qw])
	// 	printf("%s\n", el->argv[qw]);
	// printf("-------------------------------------\n");
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

// char *check_path_for_slash(t_ms *minishell, char **line)
// {
// 	char *way;
// 	int	check;

// 	check = check_bin(minishell);
// 	if (check)
// 		return (ft_strdup(minishell->line[0]));
// 	else
// 	{
// 		get_path(minishell);
// 		way = right_way(minishell);
// 		return (way);
// 	}
// 	return (NULL);
// }

// char	*pwd_check(t_ms *minishell)
// {
// 	char **dest;
// 	char *tmp;
// 	int	 i;
// 	int	j;
	
// 	i = 0;
// 	j = 0;
// 	dest = NULL;
// 	tmp = NULL;
// 	dest = malloc(sizeof(char *) * 1);
// 	if (minishell->line[0][i + 1] == '/')
// 	{
// 		while (minishell->env[++i])
// 		{
// 			if (ft_strncmp(minishell->env[i], "PWD=", 4) == 0)
// 			{
// 				dest[0] = (char *)malloc(sizeof(char *) * ft_strlen(minishell->env[i]));
// 				dest[0] = ft_strdup(minishell->env[i]);
// 			}
// 		}
// 		dest[0] = slash_path(dest[0] + 4, minishell->line[0] + 2);
// 	}
// 	else
// 	{
// 		while (minishell->env[++i])
// 		{
// 			if (ft_strncmp(minishell->env[i], "PWD=", 4) == 0)
// 			{
// 				dest[0] = (char *)malloc(sizeof(char *) * ft_strlen(minishell->env[i]));
// 				dest[0] = ft_strdup(minishell->env[i] + 4);
// 			}
// 		}
// 		i = 0;
// 		while (dest[0][i++] != '\0')
// 			;
// 		while (dest[0][i--] != '/')
// 			;
// 		while (j++ != i)
// 			tmp = ft_substr(dest[0], 0, i + 1);
// 		dest[0] = NULL;
// 		dest[0] = ft_strjoin(tmp, minishell->line[0] + 2);
// 		free(tmp);
// 	}
// 	return (dest[0]);
// }

char **record_cmd2(t_ms *minishell)
{
	int	i;
	char **dest;

	i = 0;
	while (minishell->line[i] && *minishell->line[i] != '|')
		i++;
	dest = (char **)malloc(sizeof(char *) * i);
	minishell->line[0] = check_path(minishell);
	i = 0;
	while (minishell->line[i] && *minishell->line[i] != '|')
	{
		dest[i] = ft_strdup(minishell->line[i]);
		i++;
	}
	dest[i] = NULL;
	if (minishell->line[i] && *minishell->line[i] == '|')
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
	el->back = *lst;
	(*lst)->next = el;
	*lst = el;
}


char *check_path(t_ms *minishell)
{
	char *way;
	int	check;

	check = check_bin(minishell);
	if (check)
		return (ft_strdup(minishell->line[0]));
	else
	{
		get_path(minishell);
		way = right_way(minishell);
		return (way);
	}
	return (0);
}