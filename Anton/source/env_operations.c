
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
// 	env_copy = (char **)malloc(len_argvs(env) * sizeof(char *));
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


char *value_of_variable(char *s)
{
	int len;
	int ps_val;
	char *value;

	len = 0;
	ps_val = 0;
	while (s[len] && s[len] != '=')
		len++;
	value = (char *)malloc(sizeof(char) * ((ft_strlen(s) - len) + 1));
	if (!value)
		return (NULL);
	while (s[++len])
	{
		value[ps_val] = s[len];
		ps_val++;
	}
	value[ps_val] = '\0';
	return (value);
}


char *name_of_variable(char *s)
{
	int len;
	int i;

	len = 0;
	i = 0;
	char *name;
	while (s[len] && s[len] != '=')
		len++;
	name = (char *)malloc(sizeof(char) * len + 1);
	if (!name)
		return (NULL);
	while (i <= len)
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

t_env *new_env_value(char *variable)
{
	t_env *str;

	str = (t_env *)malloc(sizeof(t_env));
	str->next = NULL;
	str->back = NULL;
	str->variable = name_of_variable(variable);
	str->value = value_of_variable(variable);
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
		if (!ft_strncmp((*env)->variable, ft_strjoin(value, "="), ft_strlen(value) + 1))
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

void	overwrite_env(t_env **env, char *variable, char *new_value)//Принимает название переменной и на какое значение изменить ее содержимое
{
	while((*env)->back)
		*env = (*env)->back;
	while (*env)
	{
		if (!ft_strncmp(variable, (*env)->variable, ft_strlen(variable)))
		{
			free((*env)->value);
			(*env)->value = ft_strdup(new_value);
			return ;
		}
		if (!(*env)->next)
			break ;
		*env = (*env)->next;
	}
}

char *value_of_env(t_env *env, char *value)
{
	while(env->back)
		env = env->back;
	while (env)
	{
		if (!ft_strncmp(value, env->value, ft_strlen(value)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

