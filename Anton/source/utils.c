#include "../include/minishell.h"

int	check_pipe_rct(t_ms *minishell, int i)
{
	if (minishell->line[i])
	{
		if (*minishell->line[i] == '>' && minishell->line[i][1] != '>')
			return (1);
		if (*minishell->line[i] == '<' && minishell->line[i][1] != '<')
			return (1);
		if (*minishell->line[i] == '<' && minishell->line[i][1] == '<')
			return (1);
		if (*minishell->line[i] == '>' && minishell->line[i][1] == '>')
			return (1);
	}
	return (0);
}

char	**record_cmd2(t_ms *minishell)
{
	int		i;
	char	**dest;
	char	**line;

	line = malloc(sizeof(char *) * 1);
	if (!minishell->line[0])
		return (NULL);
	line[0] = malloc(sizeof(char *) * ft_strlen(minishell->line[0]));
	line[0] = ft_strdup(minishell->line[0]);
	i = 0;
	while (minishell->line[i] && *minishell->line[i] != '|')
		i++;
	dest = (char **)malloc(sizeof(char *) * i + 1);
	if (check_pipe_rct(minishell, 0))
	{
		if (i >= 3)
			minishell->line[2] = ft_strdup(check_path(minishell));
	}
	else
		minishell->line[0] = check_path(minishell);
	i = 0;
	if (minishell->line[0] == NULL)
	{
		minishell->line[0] = ft_strdup(line[0]);
		dest[i] = ft_strdup(line[0]);
		i++;
	}
	i = 0;
	while (minishell->line[i] && *minishell->line[i] != '|' && *minishell->line[i] != '\0')
	{
		dest[i] = ft_strdup(minishell->line[i]);
		i++;
	}
	dest[i] = NULL;
	if (minishell->line[i] && *minishell->line[i] == '|')
		minishell->line = jopa(minishell, i);
	return (dest);
}

char	*check_path(t_ms *minishell)
{
	char	*way;
	int		check;
	int		i;

	i = 0;
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

char	*right_way(t_ms *minishell)
{
	int		i;
	int		j;
	int		fd;
	char	*res;

	if (!minishell->way)
		return (NULL);
	i = 0;
	j = 0;
	if (check_pipe_rct(minishell, i))
		j = 2;
	while (minishell->way || minishell->way[i])
	{
		if (minishell->way[i] == NULL)
			return (NULL);
		if (minishell->line == NULL)
			return (NULL);
		if (i == 0)
			res = slash_path(minishell->way[i] + 5, minishell->line[j]);
		else
			res = slash_path(minishell->way[i], minishell->line[j]);
		fd = open(res, O_RDONLY);
		free(res);
		if (fd != -1)
			break ;
		i++;
	}
	if (fd == -1)
		return (NULL);
	else
	{
		close(fd);
		return (res);
	}
}