/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:50 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:19:51 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**env_from_lists(t_env *env)
{
	char	**str;
	char	*join;
	char	*join1;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env->back)
		env = env->back;
	str = (char **)malloc(sizeof(char *) * lenlist_env(env) + 1);
	if (!str)
		return (NULL);
	while (env)
	{
		join1 = ft_strjoin(env->variable, "=");
		join = ft_strjoin(join1, env->value);
		str[i] = ft_strdup(join);
		i++;
		free(join1);
		free(join);
		env = env->next;
	}
	str[i] = NULL;
	return (str);
}

int	lenlist(t_cmd *list)
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

void	env_record(t_env **env, char **ev)
{
	int	i;

	i = -1;
	if (!ev || !*ev)
	{
		*env = NULL;
		return ;
	}
	while (ev[++i])
		env_value_add(env, new_env_value(ev[i]));
	while ((*env)->back)
		*env = (*env)->back;
	alpha_variables(*env);
	while ((*env)->back)
		*env = (*env)->back;
}

int	overwrite_env(t_env **env, char *variable, char *new_value)
{
	t_env	*temp;
	int		concat;
	char	*twin_varbs;

	temp = *env;
	concat = 0;
	if (variable[ft_strlen(variable) - 1] == '+' && new_value && *new_value)
	{
		twin_varbs = variable;
		free(twin_varbs);
		variable = ft_substr(variable, 0, ft_strlen(variable) - 1);
		concat++;
	}
	temp = getback(temp);
	while (temp)
	{
		if (!ft_strcmp(variable, temp->variable))
		{
			if (!new_value)
				return (if_not_new_value(temp));
			return (concat_or_overwrite(temp, concat, new_value));
		}
		temp = temp->next;
	}
	return (0);
}

char	*value_of_env(t_env *env, char *value)
{
	while (env && env->back)
		env = env->back;
	while (env)
	{
		if (!ft_strncmp(value, env->value, ft_strlen(value)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
