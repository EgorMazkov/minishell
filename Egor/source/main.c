/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:16:23 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/22 17:03:54 by ghumbert         ###   ########.fr       */
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
			if (minishell.input_line[0][i + 1] != '\0')
			{
				a = 0;
				while (minishell.input_line[0][i] != ' ')
				{
					a = i;
					j++;
					while (minishell.input_line[0][a] != ' ')
						a++;
					minishell.line[j] = malloc(sizeof(char) * a);
					minishell.line[j][a] = minishell.input_line[0][i];
					a++;
					i++;
				}
			}
			qwe(&minishell, &cmd, ev);
		}
		else
		{
			if (minishell.input[0])
				minishell.line = ft_split(minishell.input, ' ');
			qwe(&minishell, &cmd, ev);
		}
		print_mass(&cmd);
		j = 0;
		a = 0;
	}
}

void	qwe(t_ms *minishell, t_cmd *cmd, char **ev)
{
	get_path(minishell, ev);
	*minishell->way = right_way(minishell);
	if (*minishell->way == NULL)
		return ;
	write_to_array(cmd, minishell);
}

void	write_to_array(t_cmd *cmd, t_ms *minishell)
{
	int	i;
	int	j;
	int	len_for_line;

	i = 0;
	j = 0;
	while (minishell->line[j])
		j++;
	printf("%d\n", j);
	cmd->argv = (char **)malloc(j - 1);
	cmd->argv[i] = minishell->way[0];
	i++;
	j = 1;
	len_for_line = ft_strlen(minishell->line[j]);
	printf("%d\n", len_for_line);
	cmd->argv[i] = (char *)malloc(sizeof(char) * (len_for_line));
	
	while (minishell->line[j - 1])
	{
		cmd->argv[i] = minishell->line[j];
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

static size_t	len_for_s(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c)
		i++;
	return (i);
}

char	**split_preparser(char const *s, char c)
{
	int	i;
	int	j;
	int	double_quote;
	char	**dest;
	int		len_for_sc;

	len_for_sc = len_for_s(s, c);
	double_quote = 0;
	i = 0;
	dest = NULL;
	j = 0;
	double_quote = check_double_quote(s, '\"');
	while (s[i])
	{
		if (double_quote)
		{
			if (s[i] != double_quote)
			{
				while (s[i] != c)
				{
					printf("%d\n", len_for_sc);
					while (len_for_sc--)
					{
						dest[j][i] = s[i];
						i++;
					}
					dest[j][i] = '\0';
					printf("%s\n", dest[j]);
					break ;
				}
			}
			int a = 0;
			j++;
			len_for_sc = len_for_s(&s[i], c);
			dest[j][i] = (char)malloc(len_for_sc);
			while (s[i])
			{
				dest[j][a] = s[i];
				i++;
				a++;
			}
			printf("%s\n", dest[j]);
		}
		else
		{
			dest = ft_split(s, ' ');
			return (dest);
		}
	}
	return (dest);
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