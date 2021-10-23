/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operation_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:49 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:19:50 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_value_add(t_env **lst, t_env *el)
{
	if (!el)
		return ;
	if (!*lst)
	{
		*lst = el;
		return ;
	}
	el->back = *lst;
	(*lst)->next = el;
	*lst = el;
}

t_env	*new_env_value(char *varias)
{
	t_env	*str;
	char	*temp;

	temp = ft_strdup(varias);
	str = (t_env *)malloc(sizeof(t_env));
	str->next = NULL;
	str->next_alpha = NULL;
	str->back = NULL;
	str->back_alpha = NULL;
	str->variable = name_of_variable(temp);
	free(temp);
	str->value = value_of_variable(varias);
	return (str);
}

int	lenlist_env(t_env *list)
{
	int	i;

	i = 0;
	while (list->back)
		list = list->back;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

char	*value_of_variable(char *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	if (!s[len])
		return (NULL);
	return (ft_strdup(s + (len + 1)));
}

char	*name_of_variable(char *s)
{
	int	len;

	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	return (ft_substr(s, 0, len));
}
