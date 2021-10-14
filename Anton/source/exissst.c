#include "../include/minishell.h"


int len_argvs(char **ar)
{
	int str;

	str = 0;
	while (ar[str])
		str++;
	return (str);
}


int is_numbers_to_string (char *str)
{
	int i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	}
	return (1);
}

int is_numbers_to_arguments (char **str)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (!is_numbers_to_string(str[i]))
			return (0);
	}
	return (1);
}

int	ft_exit (char **code)
{
	if (!code || !*code)
		exit(0);	
	if (len_argvs(code) == 1)
	{
		if (!is_numbers_to_string(*code))
		{
			printf("exit\nexit: %s: numeric argument required", *code);
			exit(255);
		}
		else
			exit(ft_atoi(*code));
	}
	else
	{
		if (is_numbers_to_string(*code))
		{
			printf("exit: too many arguments\n");
			return (-1);
		}
		else
		{
			printf("exit\nexit: %s: numeric argument required", *code);
			exit(255);
		}
	}
	return (0);
}