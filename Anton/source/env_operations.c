
#include "../include/minishell.h"

// int len_argvs(char **ar)
// {
// 	int str;

// 	str = 0;
// 	while (ar[str])
// 		str++;
// 	return (str);
// }

// void	ft_argv_add (t_built *lst, char *el)
// {
// 	int str;
// 	char **env_copy;

// 	str = -1;
// 	env_copy = lst->env;
// 	lst->env = (char **)malloc((len_argvs(env_copy) + 1) * sizeof(char *));
// 	if (!lst->env)
// 		return ;
// 	lst->env[len_env(env_copy) + 1] = NULL;
// 	while (env_copy[++str])
// 		lst->env[str] = ft_strdup(env_copy[str]);
// 	lst->env[str] = ft_strdup(el);
// }

// char **ft_argvdup(char **env)//записать в листы
// {
// 	int str;
// 	char **env_copy;

// 	str = -1;
// 	env_copy = (char **)malloc(len_env(env) * sizeof(char *));
// 	if (!env_copy)
// 		return (NULL);
// 	env_copy[len_argvs(env)] = NULL;
// 	while (env[++str])
// 		env_copy[str] = ft_strdup(env[str]);//могут быть лики
// 	return (env_copy);
// }

void env_value_add (t_env **lst, t_env *el)
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

t_env *new_env_value(char *value)
{
	t_env *str;

	str = (t_env *)malloc(sizeof(t_env));
	str->next = NULL;
	str->back = NULL;
	str->value = ft_strdup(value);
	return (str);
}

void	env_record(t_env **env, char **ev)
{
	int i;

	i = -1;
	while (ev[++i])
		env_value_add(env, new_env_value(ev[i]));
}

void	value_delete(t_env **env, char *value)
{
	t_env *temp;
	t_env *del;

	while((*env)->back)
		*env = (*env)->back;
	while (*env)
	{
		if (!ft_strncmp((*env)->value, ft_strjoin(value, "="), ft_strlen(value) + 1))
		{
			del = *env;
			*env = (*env)->next;
			temp = del->back;
			if (!*env && !temp)
			{
				free(del);
				return ;
			}
			if (temp)
				temp->next = *env;
			if (*env)
				(*env)->back = temp;
			else
				*env = temp;
			free(del);
			return ;
		}	
		*env = (*env)->next;	
	}
}

void	ft_unset (t_env **env, char **value)
{
	int str;

	str = 0;
	while (value[str])
		value_delete(env, value[str++]);
}



