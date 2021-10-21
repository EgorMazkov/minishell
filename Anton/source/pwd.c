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
