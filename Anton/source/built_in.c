#include "../include/minishell.h"


char *level_down(char *s)
{
	int i;

	i = 0;
	while (s && s[i])
		i++;
	while (s[i] != '/')
		i--;
	s[i] = '\0';
	return (s);
}



char *get_variable_env(t_env *ev, char *str)
{
	while (ev && ev->back)
		ev = ev->back;
	while (ev)
	{
		if (!ft_strcmp(str, ev->variable))
			return (ev->value);
		ev = ev->next;
	}
	return (NULL);
}






int args_valid(char *ar)
{
	int str;

	str = 0;
	while (ar[str] && ar[str] != '=')
	{
		if (!ft_isalpha(ar[str]))
			return (0);
		str++;
	}
	return (1);
}




int	export_compare_not_value(t_env **ev, char *s)
{
	int i;
	char *dest;
	char *s1;

	i = -1;
	while (s[++i] && s[i] != '=')
		;
	if (s[i] == '=' && !s[i + 1])
	{
		dest = (char *)malloc(sizeof(char) * 2);
		dest[0] = 127;
		dest[1] = 0;
		while ((*ev)->next)
			*ev = (*ev)->next;
		s1 = ft_strjoin(s, dest);
		env_value_add(ev, new_env_value(s1));
		free(dest);
		free(s1);
		while ((*ev)->back)
			*ev = (*ev)->back;
		alpha_variables(*ev);
		return (1);
	}
	return (0);
}

