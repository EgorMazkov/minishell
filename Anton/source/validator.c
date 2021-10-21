/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 18:53:08 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/21 18:53:53 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		validator(t_ms *minishell, int i)
{
	if (!ft_strcmp(minishell->line[i], ">>") || \
		!ft_strcmp(minishell->line[i], ">") || \
		!ft_strcmp(minishell->line[i], "<") || \
		!ft_strcmp(minishell->line[i], "<<"))
	{
		i++;
		if (minishell->line[i] == NULL)
		{
			printf("Error bleat\n");
			return (0);
		}
		if (*minishell->line[i] == '|')
		{
			printf("Error bleat\n");
			return (0);
		}
		if (!ft_strcmp(minishell->line[i], ">>") || \
		!ft_strcmp(minishell->line[i], ">") || \
		!ft_strcmp(minishell->line[i], "<") || \
		!ft_strcmp(minishell->line[i], "<<"))
		{
			printf("Error bleat\n");
			return (0);
		}
	}
	if (*minishell->line[i] == '|')
	{
		i++;
		if (minishell->line[i] == NULL)
		{
			printf("Error bleat\n");
			return (0);
		}
		if (*minishell->line[i] == '|')
		{
			printf("Error bleat\n");
			return (0);
		}
	}
	while (minishell->line[i])
		i++;
	i--;
	if (*minishell->line[i] == '|')
	{
		printf("Error bleat\n");
		return (0);
	}
	if (!ft_strcmp(minishell->line[i], ">>") || \
	!ft_strcmp(minishell->line[i], ">") || \
	!ft_strcmp(minishell->line[i], "<") || \
	!ft_strcmp(minishell->line[i], "<<"))
	{
		printf("Error bleat\n");
		return (0);
	}
	return (1);
}