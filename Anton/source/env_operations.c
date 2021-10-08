
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


int lenlist_env (t_env *list)
{
	int i;

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

char **env_from_lists (t_env *env)
{
	char **str;
	char *join;
	char *join1;
	int i = 0;

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

	len = 0;
	ps_val = 0;
	while (s[len] && s[len] != '=')
		len++;
	return (ft_strdup(s + len + 1));
}


char *name_of_variable(char *s)
{
	int len;

	len = 0;
	while (s[len] && s[len] != '=')
		len++;
	s[len] = '\0';
	return (ft_strdup(s));
}

t_env *new_env_value(char *varias)
{
	t_env *str;
	char *temp = ft_strdup(varias);

	str = (t_env *)malloc(sizeof(t_env));
	str->next = NULL;
	str->next_alpha = NULL;
	str->back = NULL;
	str->back_alpha = NULL;
	str->variable = name_of_variable(temp);
	str->value = value_of_variable(varias);
	return (str);
}

void	env_record(t_env **env, char **ev)
{
	int i;

	i = -1;
	if (!*ev)
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

void	value_delete(t_env **env, char *value)
{
	t_env *temp;
	t_env *del;

	while((*env)->back)
		*env = (*env)->back;
	temp = *env;
	while (*env)
	{
		if (!ft_strcmp((*env)->variable, value))
		{
			del = *env;
			*env = (*env)->next;
			temp = del->back;
			if (!*env && !temp)
			{
				del->value = NULL;//    leaks
				del->variable = NULL;
				free(del);
				return ;
			}
			if (temp)
				temp->next = *env;
			if (*env)
				(*env)->back = temp;
			else
				*env = temp;
			if (del->back_alpha)
				del->back_alpha->next_alpha = NULL;
			if (del->next_alpha)
				del->next_alpha->back_alpha = NULL;
			free(del->value);
			free(del->variable);
			del->value = NULL;//    leaks
			del->variable = NULL;//    leaks
			del->next = NULL;//    leaks
			del->next_alpha = NULL;//    leaks
			del->back = NULL;//    leaks
			del->back_alpha = NULL;//    leaks
			free(del);
			return ;
		}	
		*env = (*env)->next;
	}
	if (!*env)
		*env = temp;
}

void	ft_unset (t_env **env, char **value)
{
	int str;

	str = 0;
	while (value[str])
		value_delete(env, value[str++]);
	while ((*env)->back)
		*env = (*env)->back;
	alpha_variables(*env);
}

int	overwrite_env(t_env **env, char *variable, char *new_value)//Принимает название переменной и на какое значение изменить ее содержимое
{
	t_env *temp;
	int concat;
	char *twin_varbs;

	temp = *env;
	concat = 0;
	if (variable[ft_strlen(variable) - 1] == '+' && new_value && *new_value)
	{
		twin_varbs = variable;
		free(twin_varbs);//lkjnklkm
		variable = ft_substr(variable, 0, ft_strlen(variable) - 1);
		concat++;
	}
	while(temp->back)
		*env = temp->back;
	while (temp)
	{
		if (!ft_strcmp(variable, temp->variable))
		{
			if (!new_value)
			{
				temp->value = NULL;
				return (1);
			}
			if (concat)
			{
				twin_varbs = temp->value;
				temp->value = ft_strjoin(temp->value, new_value);
				free(twin_varbs);
			}
			else
			{
				free(temp->value);
				temp->value = ft_strdup(new_value);
			}
			return (1);
		}
		temp = temp->next;
	}
	return (0);
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

