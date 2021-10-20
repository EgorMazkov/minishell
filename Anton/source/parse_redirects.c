#include "../include/minishell.h"




int redirect_count (char **argv)
{
	int count;
	int i;

	count = 0;
	i = -1;
	while (argv[++i])
		if (!ft_strcmp(argv[i], ">>") || \
		!ft_strcmp(argv[i], ">") || \
		!ft_strcmp(argv[i], "<") || \
		!ft_strcmp(argv[i], "<<"))
			count++;
	return (count * 2);
}

char**	record_redicts(char **argv)
{
	int str;
	int i;
	char **temp;

	str = 0;
	i = 0;
	temp = (char **)malloc((redirect_count(argv) + 1) * sizeof(char *));
	while (argv[str])
	{
		if (!ft_strcmp(argv[str], ">>") || \
		!ft_strcmp(argv[str], ">") || \
		!ft_strcmp(argv[str], "<") || \
		!ft_strcmp(argv[str], "<<"))
		{
			temp[i] = ft_strdup(argv[str]);
			temp[i + 1] = ft_strdup(argv[str + 1]);
			i += 2;
			str += 2;
			continue;
		}
		str++;
	}
	temp[i] = NULL;
	return (temp);
}

char **rewrite_cmd(char **argv)
{
	int i;
	int str;
	char **temp;

	i = 0;
	str = 0;
	temp = (char **)malloc(((len_tab(argv) - redirect_count(argv)) + 1) * sizeof(char *));
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], ">>") || \
		!ft_strcmp(argv[i], ">") || \
		!ft_strcmp(argv[i], "<") || \
		!ft_strcmp(argv[i], "<<"))
		{
			i += 2;
			continue;
		}
		temp[str] = ft_strdup(argv[i]);
		str++;
		i++;
	}
	temp[str] = NULL;
	return (temp);
}



