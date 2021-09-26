/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:16:23 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/26 16:58:48 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
echo "123 123 123 123 123 123 1"
*/

int	main(int argc, char **argv, char **ev)
{
	t_ms	minishell;
	t_cmd	cmd;
	t_se	se;
	int		j;
	int		a;
	int		i;
	int		double_quote;

	a = 0;
	j = 0;
	i = 0;
	double_quote = 0;
	null_struct(&minishell, &cmd);
	appropriation(argc, argv, ev, &minishell);
	while (1)
	{
		minishell.input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		// minishell.input = "cat -e | echo -n";
		minishell.input_line = &minishell.input;
		double_quote = preparser(&minishell, &se);
		if (double_quote)
		{
			minishell.line = malloc(sizeof(char **) * 1);
			minishell.line[j] = malloc(sizeof(char *) * se.start - 1);
			while (a != double_quote - 1)
			{
				minishell.line[j][a] = minishell.input_line[j][a];
				a++;
			}
			// printf("%s\n", minishell.line[j]);
			j++;
			i = a + 2;
			a = 0;
			minishell.line[j] = malloc(sizeof(char *) * (se.end - se.start - 1));
			while (minishell.input_line[0][i] != '\"' && minishell.input_line)
			{
				minishell.line[j][a] = minishell.input_line[0][i];
				a++;
				i++;
			}
			// printf("%s\n", minishell.line[j]);
			if (minishell.input_line[0][i + 1] != '\0')
			{
				a = 0;
				minishell.line[j] = malloc(sizeof(char) * a);
				while (minishell.input_line[0][i] != ' ')
				{
					a = i;
					j++;
					while (minishell.input_line[0][a] != ' ')
						a++;
					minishell.line[j][a] = minishell.input_line[0][i];
					a++;
					i++;
				}
			}
			if (!minishell.line)
				continue ;
			qwe(&minishell, &cmd, ev, 0);
		}
		else
		{
			if (minishell.input[0])
				minishell.line = ft_split(minishell.input, ' ');
			if (!minishell.line)
				continue ;
			qwe(&minishell, &cmd, ev, 0);
		}
		j = 0;
		a = 0;
		printf("%s\n", cmd.argv[0]);
		printf("%s\n", cmd.argv[1]);
		null_argv(&cmd);
		// printf("%s\n", cmd.argv[0]);
		// printf("%s\n", cmd.argv[1]);
	}
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

void	qwe(t_ms *minishell, t_cmd *cmd, char **ev, int check)
{
	int	j;

	j = check;
	check = check_bin(minishell, check);
	if (check)
	{
		cmd->argv[j] = minishell->line[j];
		// printf("1 :%s\n", cmd->argv[j]);
		j++;
		if (minishell->line[j])
			write_to_array(cmd, minishell, j);
		return ;
	}
	get_path(minishell, ev);
	minishell->way[0] = right_way(minishell, j);
	if (*minishell->way == NULL)
	{
		printf("\033[0;29mDungeonMaster: \033[0;29m %s :", minishell->line[0]);
		printf("command not found\n");
		return ;
	}
	cmd->argv[j] = minishell->way[0];
	// printf("1 :%s\n", cmd->argv[j]);
	if (minishell->line[++j])
		write_to_array(cmd, minishell, 1);
}

void	write_to_array(t_cmd *cmd, t_ms *minishell, int j)
{
	int	i;
	int	a;
	int	len_for_line;

	i = 1;
	a = 0;
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
	while (minishell->line[j])
	{
		if (minishell->line[j][a] == '|')
		{
			cmd->operator = '|';
			j++;
			qwe(minishell, cmd, minishell->env, j);
			return ;
		}
		cmd->argv[i] = minishell->line[j];
		// printf("1 2 : %s\n", cmd->argv[i]);
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


/*
		j++;
		while (s[i])
		{
			dest[j][a] = s[i];
			i++;
			a++;
		}
		printf("%s\n", dest[j]);
		*/




































































