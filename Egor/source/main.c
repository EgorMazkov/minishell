#include "../include/minishell.h"

void	null_struct(t_ms *minishell, t_cmd *cmd)
{
	minishell->argc = 0;
	minishell->argv = NULL;
	minishell->env = NULL;
	minishell->i = 0;
	minishell->input = NULL;
	minishell->line = NULL;
	minishell->way = NULL;
	cmd->file = NULL;
	cmd->util_cmd = NULL;
}

void	get_path(t_ms *minishell, char **ev)
{
	int	i;

	i = -1;
	while (ev[++i])
	{
		if (ft_strncmp(ev[i], "PATH=", 5) == 0)
			minishell->way = ft_split(minishell->env[i], ':');
	}
}

char	*slash_path(char *way, char *line)
{
	char	*res;

	line = ft_strjoin("/", line);
	res = ft_strjoin(way, line);
	free(line);
	return (res);
}

char	*right_way(t_ms *minishell)
{
	int		i;
	int		fd;
	char	*res;

	i = 0;
	while (minishell->way[i])
	{
		res = slash_path(minishell->way[i], minishell->line[0]);
		fd = open(res, O_RDONLY);
		free(res);
				if (fd != -1)
			break ;
		i++;
	}
	if (fd == -1)
		return (NULL);
	else
		return (res);
}

void	appropriation(int argc, char **argv, char **ev, t_ms *minishell)
{
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->env = ev;
}

int main(int argc, char **argv, char **ev)
{
	t_ms	minishell;
	t_cmd	cmd;
	null_struct(&minishell, &cmd);
	appropriation(argc, argv, ev, &minishell);
	int	i;
	int	len_for_line;
	int	j;

	i = 0;
	j = 1;
	while (1)
	{
		minishell.input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		// minishell.input = "cat -e";
		if (minishell.input[0])
			minishell.line = ft_split(minishell.input, ' ');
		get_path(&minishell, ev);
		*minishell.way = right_way(&minishell);
		if (*minishell.way == NULL)
		{
			printf("EEEE YES enter commands normally\n");
			break ;
		}
		len_for_line = ft_strlen(minishell.way[0]);
		cmd.argv = (char **)malloc(3);
		cmd.argv[i] = minishell.way[0];
		printf("argv[0] %s\n", cmd.argv[i]);
		i++;
		while (minishell.line[i])
		{
			len_for_line = ft_strlen(minishell.line[j]);
			cmd.argv[i] = (char *)malloc(sizeof(char) * (len_for_line));
			cmd.argv[i] = minishell.line[j];
			printf("argv[0] %s\n", cmd.argv[i]);
			i++;
		}
		// printf("argv[0] %s\n", cmd.argv[2]);
	}
}

	// fd = open("our way",  O_WRONLY | O_TRUNC | O_CREAT, 0666);

	// pipex.comm == minishell.line
	// pipex.path_priem == minishell.way
	//