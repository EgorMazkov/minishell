
#include "../include/minishell.h"

int len_env(char **ar)
{
	int str;

	str = 0;
	while (ar[str])
		str++;
	return (str);
}

void	ft_env_add (t_built *lst, char *el)
{
	int str;
	char **env_copy;

	str = -1;
	env_copy = lst->env;
	lst->env = (char **)malloc((len_env(env_copy) + 1) * sizeof(char *));
	if (!lst->env)
		return ;
	lst->env[len_env(env_copy) + 1] = NULL;
	while (env_copy[++str])
		lst->env[str] = ft_strdup(env_copy[str]);
	lst->env[str] = ft_strdup(el);
}

char **ft_envdup(char **env)//записать в листы
{
	int str;
	char **env_copy;

	str = -1;
	env_copy = (char **)malloc(len_env(env) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	env_copy[len_env(env)] = NULL;
	while (env[++str])
		env_copy[str] = ft_strdup(env[str]);//могут быть лики
	return (env_copy);
}
