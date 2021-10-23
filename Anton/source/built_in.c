/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:44 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:19:45 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *command)
{
	if (!command)
		return (0);
	if (!ft_strcmp("echo", command))
		return (1);
	else if (!ft_strcmp("unset", command))
		return (1);
	else if (!ft_strcmp("export", command))
		return (1);
	else if (!ft_strcmp("cd", command))
		return (1);
	else if (!ft_strcmp("exit", command))
		return (1);
	else if (!ft_strcmp("env", command))
		return (1);
	else if (!ft_strcmp("pwd", command))
		return (1);
	return (0);
}

char	*level_down(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
		i++;
	while (s[i] != '/')
		i--;
	s[i] = '\0';
	return (s);
}

char	*get_variable_env(t_env *ev, char *str)
{
	while (ev && ev->back)
		ev = ev->back;
	while (ev)
	{
		if (!ft_strcmp(str, ev->variable))
			return (ev->value);
		ev = ev->next;
	}
	return (NULL);
}

int	args_valid(char *ar)
{
	int	str;

	str = 0;
	while (ar[str] && ar[str] != '=')
	{
		if (ar[str] == '+' && ar[str + 1] == '=')
			return (1);
		if (!ft_isalpha(ar[str]))
			return (0);
		str++;
	}
	return (1);
}

int	export_compare_not_value(char *s)
{
	int		i;

	i = -1;
	while (s[++i] && s[i] != '=')
		;
	if (s[i] == '=' && !s[i + 1])
		return (1);
	return (0);
}
