/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 16:19:53 by tharodon          #+#    #+#             */
/*   Updated: 2021/10/23 16:19:54 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_variables(t_env *temp)
{
	while (temp && temp->back_alpha)
		temp = temp->back_alpha;
	while (temp)
	{
		if (temp->variable && temp->variable[0])
			printf("declare -x %s", temp->variable);
		if (temp->variable && temp->value && *temp->value && \
		!ft_strcmp(temp->value, "\"\""))
			printf("=\"\"\n");
		else if (temp->variable && temp->value && *temp->value)
			printf("=\"%s\"\n", temp->value);
		else
			printf("\n");
		temp = temp->next_alpha;
	}
}

static int	variable_add_to_export(t_env **ev, char **arg, \
int i, int *not_valid)
{
	char	*vals;
	char	*vars;

	if (!args_valid(arg[i]) || export_compare_not_value(arg[i]))
	{
		*not_valid = 1;
		printf("%s: not a valid identifier\n", arg[i]);
	}
	else
	{
		vals = value_of_variable(arg[i]);
		vars = name_of_variable(arg[i]);
		if (!overwrite_env(ev, vars, vals))
		{
			while (*ev && (*ev)->next)
				*ev = (*ev)->next;
			env_value_add(ev, new_env_value(arg[i]));
			while ((*ev)->back)
				*ev = (*ev)->back;
			alpha_variables(*ev);
		}
		free(vals);
		free(vars);
	}
	return (0);
}

int	ft_export(t_env **ev, char **arg)
{
	t_env	*temp;
	int		i;
	int		not_valid;

	temp = *ev;
	not_valid = 0;
	i = -1;
	if (!arg || !*arg)
		print_variables(temp);
	else
	{
		while (arg[++i])
			variable_add_to_export(ev, arg, i, &not_valid);
	}
	if (not_valid)
		return (-1);
	return (1);
}
