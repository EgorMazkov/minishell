/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:20:05 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:23:11 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	null_env(t_env **del)
{
	(*del)->next = NULL;
	(*del)->next_alpha = NULL;
	(*del)->back = NULL;
	(*del)->back_alpha = NULL;
}

void	cut_and_free_varias(t_env **env, t_env *temp)
{
	t_env	*del;

	del = *env;
	*env = (*env)->next;
	temp = del->back;
	if (!*env && !temp)
	{
		free_env(&del);
		return ;
	}
	if (temp)
		temp->next = *env;
	if (*env)
		(*env)->back = temp;
	else
		*env = temp;
	if (del->back_alpha)
		del->back_alpha->next_alpha = NULL;
	if (del->next_alpha)
		del->next_alpha->back_alpha = NULL;
	null_env(&del);
	free_env(&del);
}

void	value_delete(t_env **env, char *value)
{
	t_env	*temp;

	while ((*env)->back)
		*env = (*env)->back;
	temp = *env;
	while (*env)
	{
		if (!ft_strcmp((*env)->variable, value))
		{
			cut_and_free_varias(env, temp);
			return ;
		}
		*env = (*env)->next;
	}
	if (!*env)
		*env = temp;
}

void	ft_unset(t_env **env, char **value)
{
	int	str;

	str = 0;
	if (value && value[0])
	{
		while (value[str])
			value_delete(env, value[str++]);
		while (*env && (*env)->back)
			*env = (*env)->back;
		alpha_variables(*env);
	}
}
