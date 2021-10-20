
#include "../include/minishell.h"



char **env_from_lists (t_env *env)
{
	char **str;
	char *join;
	char *join1;
	int i = 0;

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



void	env_record(t_env **env, char **ev)
{
	int i;

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

char *value_of_env(t_env *env, char *value)
{
	while(env && env->back)
		env = env->back;
	while (env)
	{
		if (!ft_strncmp(value, env->value, ft_strlen(value)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

