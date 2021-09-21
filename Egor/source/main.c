/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:16:23 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/21 17:06:49 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **ev)
{
	t_ms	minishell;
	t_cmd	cmd;
	int		a;

	a = 0;
	null_struct(&minishell, &cmd);
	appropriation(argc, argv, ev, &minishell);
	while (1)
	{
		minishell.input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		if (minishell.input[0])
			minishell.line = split_preparser(minishell.input, ' ');
		get_path(&minishell, ev);
		*minishell.way = right_way(&minishell);
		if (*minishell.way == NULL)
			continue ;
		write_to_array(&cmd, &minishell);
		print_mass(&cmd);
	}
}

void	write_to_array(t_cmd *cmd, t_ms *minishell)
{
	int	i;
	int	j;
	int	len_for_line;

	i = 0;
	j = 1;
	len_for_line = ft_strlen(minishell->way[0]);
	cmd->argv = (char **)malloc(len_for_line);
	cmd->argv[i] = minishell->way[0];
	i++;
	// parser(minishell, i);
	while (minishell->line[j])
	{
		len_for_line = ft_strlen(minishell->line[j]);
		cmd->argv[i] = (char *)malloc(sizeof(char) * (len_for_line));
		cmd->argv[i] = minishell->line[j];
		i++;
		j++;
	}
}


/*
echo "123 123 123 123 123 123 1"
*/


int	check_double_quote(char const *s, char c)
{
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
	// dest = NULL;
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