/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operation_utils_overwrite.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 23:07:31 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:19:51 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*getback(t_env *temp)
{
	while (temp && temp->back)
		temp = temp->back;
	return (temp);
}

int	if_not_new_value(t_env *temp)
{
	free_str(temp->value);
	temp->value = NULL;
	return (1);
}

int	concat_or_overwrite(t_env *temp, int concat, char *new_value)
{
	char	*twin_varbs;

	if (concat)
	{
		twin_varbs = temp->value;
		temp->value = ft_strjoin(temp->value, new_value);
		free(twin_varbs);
	}
	else
	{
		free(temp->value);
		temp->value = ft_strdup(new_value);
	}
	return (1);
}
