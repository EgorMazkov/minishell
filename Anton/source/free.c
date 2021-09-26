#include "../include/minishell.h"

void	free_all(t_env **env)
{
	t_env *temp;

	while ((*env)->back)
		*env = (*env)->back;
	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free(temp->variable);
		free(temp->value);
		free(temp);
	}
}