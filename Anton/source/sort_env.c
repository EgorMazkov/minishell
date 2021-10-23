/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:20:04 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:20:05 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

t_env	*get_maxmin_variable(t_env *variable, _Bool min_max)
{
	t_env	*temp;
	t_env	*min;
	int		difference;

	temp = variable;
	min = variable;
	difference = 0;
	while (temp && temp->back)
		temp = temp->back;
	while (temp)
	{
		if (min_max == MAX && \
		ft_strcmp(min->variable, temp->variable) < difference)
			min = temp;
		if (min_max == MIN && \
		ft_strcmp(min->variable, temp->variable) > difference)
			min = temp;
		temp = temp->next;
	}
	return (min);
}

t_env	*get_up_neighbour(t_env *el)
{
	t_env	*start;
	t_env	*tmp;

	start = el;
	tmp = get_maxmin_variable(el, MAX);
	if (tmp == el)
		return (NULL);
	while (start->back)
		start = start->back;
	while (start)
	{
		if (ft_strcmp(start->variable, tmp->variable) < 0 \
		&& ft_strcmp(start->variable, el->variable) > 0)
			tmp = start;
		start = start->next;
	}
	return (tmp);
}

void	alpha_variables(t_env *env)
{
	t_env	*min;
	t_env	*max;

	min = get_maxmin_variable(env, MIN);
	max = get_maxmin_variable(env, MAX);
	while (min != max)
	{
		min->next_alpha = get_up_neighbour(min);
		if (min->next_alpha)
			min->next_alpha->back_alpha = min;
		min = min->next_alpha;
	}
}
