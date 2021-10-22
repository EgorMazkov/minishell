/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assistant_validator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 23:37:59 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/22 23:38:59 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	validator(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->back)
		cmd = cmd->back;
	while (cmd->argv)
	{
		if (cmd->argv[i])
		{
			if (is_rdct(cmd->argv[i]))
			{
				if (!val_three(cmd, &i))
					return (0);
				continue ;
			}
			if (valid_four(&cmd, &i))
				continue ;
			i++;
			continue ;
		}
		else
			if (valid_two(&cmd, &i))
				return (1);
	}
	return (1);
}
