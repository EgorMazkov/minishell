/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gavn_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:00:17 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/22 22:00:41 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	trim(t_cmd **cmd, t_dollar *dollar)
{
	char	*dest;

	while (dollar->a != dollar->j)
	{
		if ((*cmd)->argv[dollar->i][0] == '\"')
		{
			dest = (*cmd)->argv[dollar->i];
			(*cmd)->argv[dollar->i] = ft_strtrim((*cmd)->argv[dollar->i], "\"");
			free_str(dest);
			dollar->a++;
			if (dollar->a == dollar->j)
				break ;
		}
		if ((*cmd)->argv[dollar->i][0] == '\'')
		{
			dest = (*cmd)->argv[dollar->i];
			(*cmd)->argv[dollar->i] = ft_strtrim((*cmd)->argv[dollar->i], "\'");
			free_str(dest);
			dollar->a++;
			if (dollar->a == dollar->j)
				break ;
		}
		continue ;
	}
}
