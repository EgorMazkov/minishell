/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:16:23 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/29 14:37:24 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
echo "123 123 123 123 123 123 1"
*/

int	main(int argc, char **argv, char **ev)
{
	t_ms	*minishell = NULL;
	t_cmd	*cmd = NULL;
	// t_se	se;
	int		j;
	int		a;
	int		i;
	int		double_quote;

	minishell = (t_ms *)malloc(sizeof(t_ms));
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	a = 0;
	j = 0;
	i = 0;
	double_quote = 0;
	null_struct(minishell, cmd);
	appropriation(argc, argv, ev, minishell);
	minishell->input_line = (char **)malloc(sizeof(char *) + 1);
	minishell->input_line[1] = NULL;
	while (1)
	{
		cmd->argv = malloc(sizeof(char *));
		minishell->input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		// minishell->input = "cat -e | make";
		if (minishell->input[0])
			minishell->line = ft_split_for_minishell(minishell->input, ' ');
		if (!minishell->line)
			continue ;
		qwe(minishell, cmd, 0, 0);
		j = 0;
		a = 0;
		printf("exit\n");
		printf("%s\n", cmd->argv[0]);
		printf("%s\n", cmd->argv[1]);
		// null_argv(&cmd);
	}
	// printf("%s\n", cmd.argv[1]);
}

void	null_argv(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd->argv[i])
	{
		cmd->argv[i] = NULL;
		i++;
	}
}

void	free_argv(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
}

int		check_bin(t_ms *minishell, int i)
{
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

void	qwe(t_ms *minishell, t_cmd *cmd, int check, int i)
{
	int	j;

	j = check;
	check = check_bin(minishell, check);
	if (check)
	{
		cmd->argv[i] = ft_strdup(minishell->line[j]);
		j++;
		if (minishell->line[j])
			write_to_array(cmd, minishell, j);
		return ;
	}
	get_path(minishell);
	minishell->way[0] = right_way(minishell, j);
	if (*minishell->way == NULL)
	{
		printf("\033[0;29mDungeonMaster: \033[0;29m %s :", minishell->line[0]);
		printf("command not found\n");
		free (cmd->argv);
		return ;
	}
	// if (minishell->i)
	// 	cmd->argv = malloc(sizeof(char *));
	cmd->argv[i] = ft_strdup(minishell->way[0]);
	if (minishell->line[++j])
		write_to_array(cmd, minishell, 1);
}

void	write_to_array(t_cmd *cmd, t_ms *minishell, int j)
{
	int	i;
	int	len_for_line;

	i = 1;
	len_for_line = 0;

	if (minishell->line[j])
		len_for_line = ft_strlen(minishell->line[j]);
	else
	{
		i = 0;
		j = 0;
		len_for_line = ft_strlen(minishell->line[j]);
	}
	cmd->argv[i] = (char *)malloc(sizeof(char) * (len_for_line));
	cmd->argv[i][len_for_line] = '\0';
	while (minishell->line[j])
	{
		if (*minishell->line[j] == '|')
		{
			cmd->operator = '|';
			i = 0;
			j++;
			minishell->i = 1;
			cmd = cmd->next;
			qwe(minishell, cmd, j, i);
			return ;
		}
		cmd->argv[i] = ft_strdup(minishell->line[j]);
		i++;
		j++;
	}
}

int	check_double_quote(char const *s, char c)
{
	(void)c;
	int	i;
	int	double_quote;

	double_quote = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\"')
		{
			double_quote = i;
			return (double_quote);
		}
		i++;
	}
	return (double_quote);
}
