#include "../include/minishell.h"

// int	check_pipe_rct(t_ms *minishell, int i)
// {
// 	if (minishell->line[i])
// 	{
// 		if (*minishell->line[i] == '>' && minishell->line[i][1] != '>')
// 			return (1);
// 		if (*minishell->line[i] == '<' && minishell->line[i][1] != '<')
// 			return (1);
// 		if (*minishell->line[i] == '<' && minishell->line[i][1] == '<')
// 			return (1);
// 		if (*minishell->line[i] == '>' && minishell->line[i][1] == '>')
// 			return (1);
// 	}
// 	return (0);
// }

// int	check_pipe_for_qoute(t_ms *minishell, int i)
// {
// 	if (*minishell->line[i] == '|')
// 	{
// 		if (*minishell->line[i + 1] == '\'')
// 			return (1);
// 		else
// 			return (0);
// 	}
// 	else
// 		return (1);
// }

char **record_cmd2(t_ms *minishell)
{
	int i;
	char **dest;

	i = 0;
	while (minishell->line[i] && minishell->line[i][0] != '|')
		i++;
	dest = (char **)malloc((sizeof(char *) * i) + 1);

	i = 0;
	while (minishell->line[i] && minishell->line[i][0] != '|' && *minishell->line[i] != '\0')
	{
		dest[i] = ft_strdup(minishell->line[i]);
		i++;
	}
	dest[i] = NULL;
	if (minishell->line[i] && *minishell->line[i] == '|')
		minishell->line = jopa(minishell, i);
	return (dest);
}

void path(t_cmd **cmd, t_ms *minishell)
{
	char *line;
	char *dest;

	line = NULL;
	while ((*cmd)->argv[0])
	{
		get_path(minishell);
		if (check_bin(*cmd))
		{
			if (minishell->way)
				free_argv(minishell->way);
			minishell->way = NULL;
			if ((*cmd)->next)
			{
				*cmd = (*cmd)->next;
				continue;
			}
			return ;
		}
		if (minishell->way)
		{
			line = right_way(*cmd, minishell);
		}
		if (line && *line)
		{
			dest = (*cmd)->argv[0];
			(*cmd)->argv[0] = ft_strdup(line);
			free(dest);
			free(line);
		}
		if ((*cmd)->next)
		{
			*cmd = (*cmd)->next;
			continue;
		}
		else
		{
			// if (line)
				// free_str(line);
			// line = NULL;
			// printf("argv[0]: %s\n", (*cmd)->argv[0]);
			return;
		}
	}
}

int check_bin(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->argv)
	{
		if (!ft_strncmp(cmd->argv[i], "cd", 2))
			return (1);
		if (!ft_strncmp(cmd->argv[i], "env", 3))
			return (1);
		if (!ft_strncmp(cmd->argv[i], "echo", 4))
			return (1);
		if (!ft_strncmp(cmd->argv[i], "pwd", 3))
			return (1);
		if (!ft_strncmp(cmd->argv[i], "unset", 5))
			return (1);
		if (!ft_strncmp(cmd->argv[i], "exit", 4))
			return (1);
		if (!ft_strncmp(cmd->argv[i], "export", 6))
			return (1);
	}
	return (0);
}

char *right_way(t_cmd *cmd, t_ms *minishell)
{
	int fd;
	char *res;
	int i;

	i = 0;
	while (minishell->way && minishell->way[i])
	{
		if (minishell->way[i] == NULL)
			return (NULL);
		if (minishell->line == NULL)
			return (NULL);
		if (i == 0)
			res = slash_path(minishell->way[i] + 5, cmd->argv[0]);
		else
			res = slash_path(minishell->way[i], cmd->argv[0]);
		fd = open(res, O_RDONLY);
		if (fd != -1)
			break;
		free(res);
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
