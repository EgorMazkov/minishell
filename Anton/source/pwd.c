/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:02:54 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/22 22:02:55 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_pwd(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp && temp->back)
		temp = temp->back;
	while (temp)
	{
		if (!ft_strcmp("PWD", temp->variable))
		{
			ft_putstr_fd(temp->value, 1);
			ft_putstr_fd("\n", 1);
		}
		temp = temp->next;
	}
	return (1);
}
