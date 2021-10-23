/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:48 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:19:49 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_slash_n(char **str)
{
	int	i;
	int	ar;

	ar = 0;
	while (str[ar])
	{
		i = 0;
		if (str[ar][i] != '-' || (str[ar][i] == '-' && ft_strlen(str[ar]) == 1))
			return (ar);
		if (str[ar][i] == '-')
		{
			while (str[ar][++i])
				if (str[ar][i] != 'n')
					return (ar);
		}
		else
			return (ar);
		ar++;
	}
	return (ar);
}

void	ft_echo(char **arg)
{
	int	str;
	int	line;
	int	flag_n;

	str = is_slash_n(arg);
	if (str)
		flag_n = 1;
	while (arg[str])
	{
		line = -1;
		while (arg[str][++line])
			write(1, &arg[str][line], 1);
		if (arg[str + 1])
			write(1, " ", 1);
		str++;
	}
	if (!flag_n)
		write(1, "\n", 1);
}
