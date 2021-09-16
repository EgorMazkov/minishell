#include "../include/minishell.h"

void	null_struct(t_ms *minishell)
{
	minishell->argc = 0;
	minishell->argv = NULL;
	minishell->env = NULL;
	minishell->i = 0;
	minishell->input = NULL;
	minishell->line = NULL;
	minishell->way = NULL;
}

void	get_path(t_ms *minishell)
{
	int	i;

	i = -1;
	while (minishell->env[++i])
	{
		if (ft_strncmp(minishell->env[i], "PATH=", 5) == 0)
			minishell->way = ft_split(minishell->env[i], ':');
	}
}

void	appropriation(int argc, char **argv, char **ev, t_ms *minishell)
{
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->env = ev;
}

void	slash_path(t_ms *minishell)
{
	char	*res;

	res = ft_strjoin(*minishell->way, "/");
	res = ft_strjoin(res, *minishell->line);
	minishell->way = &res;
}

int main(int argc, char **argv, char **ev)
{
	t_ms	minishell;
	null_struct(&minishell);
	appropriation(argc, argv, ev, &minishell);
	while (1)
	{
		minishell.input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		if (minishell.input[0])
			minishell.line = ft_split(minishell.input, ' ');
		get_path(&minishell);
		slash_path(&minishell);
		printf("%s\n", minishell.way[0]);
	}
}

	// fd = open("our way",  O_WRONLY | O_TRUNC | O_CREAT, 0666);