/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 21:59:22 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/22 21:59:23 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	env_to_lists(t_env **env, char **ev)
{
	char	*cw;

	if (ev && *ev)
	{
		cw = getcwd(NULL, 0);
		env_record(env, ev);
		overwrite_env(env, "OLDPWD", cw);
		free(cw);
		if (!get_variable_env(*env, "SHLVL"))
			return (1);
		cw = ft_itoa(ft_atoi(get_variable_env(*env, "SHLVL")) + 1);
		overwrite_env(env, "SHLVL", cw);
		free(cw);
		return (1);
	}
	return (0);
}

void	ft_env(t_env *ev)
{
	while (ev && ev->back)
		ev = ev->back;
	while (ev)
	{
		if (ev->value && *ev->value)
			printf("%s=%s\n", ev->variable, ev->value);
		ev = ev->next;
	}
}