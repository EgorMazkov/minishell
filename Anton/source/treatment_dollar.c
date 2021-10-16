/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treatment_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 10:26:36 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/16 12:25:51 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	preparser_dollar(t_cmd **cmd, t_ms *minishell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*cmd)->argv)
	{
		while ((*cmd)->argv[i][j] != '$' && (*cmd)->argv[i][j] != '\0')
			j++;
		if ((*cmd)->argv[i][j] == '$')
			record_dollar(cmd, i, minishell);
		j = 0;
		i++;
		if ((*cmd)->argv[i] == NULL)
		{
			if ((*cmd)->next)
				*cmd = (*cmd)->next;
			else
				return ;
			i = 0;
			j = 0;
		}
	}
}

void	record_dollar(t_cmd **cmd, int i, t_ms *minishell)
{
	char **line;

	line = 0;
	line = (char **)malloc(sizeof(char *) * 1);
	if ((*cmd)->argv[i][0] == '\'')
	{
		line[0] = ft_strtrim((*cmd)->argv[i], "\'");
		ft_strtrim(line[0], "\'");
		(*cmd)->argv[i] = ft_strdup(line[0]);
		return ;
	}
	get_path_dollar(cmd, i, minishell);
}

void	get_path_dollar(t_cmd **cmd, int a, t_ms *minishell)
{
	char **dest;
	int i;

	i = 0;
	dest = (char **)malloc(sizeof(char *) * 1);
	if ((*cmd)->argv[a][0] == '\"')
		dest[0] = ft_strtrim((*cmd)->argv[a], "\"");
	else
		dest[0] = ft_strdup((*cmd)->argv[a]);
	dest[0] = ft_strdup(&dest[0][i + 1]);
	dest[0] = dollar_tolower(dest);
	i = -1;
	while (minishell->env[++i])
	{
		if (ft_strncmp(minishell->env[i], dest[0], ft_strlen(dest[0])) == 0)
		{
			(*cmd)->argv[a] = ft_strdup(minishell->env[i] + ft_strlen(dest[0]) + 1);
			dest[0] = NULL;
			free(dest);
			return ;
		}
	}
}

char	*dollar_tolower(char **dest)
{
	int	i;

	i = 0;
	while (dest[0][i] != '\0')
	{
		if (dest[0][i] >= 97 && dest[0][i] <= 122)
			dest[0][i] = dest[0][i] - 32;
		i++;
	}
	return (dest[0]);
}