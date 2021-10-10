#include "../include/minishell.h"

void	lstadd_rdct(t_rdct **lst, t_rdct *el)
{
	if (!el)
		return;
	if (!*lst)
	{
		*lst = el;
		return;
	}
	el->back = *lst;
	(*lst)->next = el;
	*lst = el;
}

void	*new_rcdt(t_ms *minishell)
{
	t_rdct	*el;
	int		j;

	j = 0;
	el = (t_rdct *)malloc(sizeof(t_rdct));
	if (!el)
		return (NULL);
	el->rdct = check_record_rdct(minishell);
	el->next = NULL;
	el->back = NULL;
	el->file = check_record_file(minishell, el->rdct);
	return (el);
}

// void	record_cmd_rc(t_cmd **cmd, t_ms *minishell)
// {
// 	int	i;

// 	i = 0;
// 	(void)cmd;
// 	while (minishell->line[i])
// 	{
// 		if (*minishell->line[i] == '>' || *minishell->line[i] == '<')
// 			record_cmd_rc_two(minishell);
// 		i++;
// 	}
// }

char	**record_cmd_rc_two(t_ms *minishell)
{
	int i;
	char **dest;

	i = 0;
	// line = malloc(sizeof(char *) * 1);
	// line[0] = malloc(sizeof(char *) * ft_strlen(minishell->line[0]));
	// line[0] = ft_strdup(minishell->line[0]);
	// while (*minishell->line[i] != '<' && *minishell->line[i] != '>')
	// {
	// 	printf("%s\n", minishell->line[i]);
	// 	i++;
	// }
	new_rcdt(minishell);
	printf("Error");
	printf("%d\n", minishell->rdct->rdct);
	while (1)
		;
	return (dest);
}

int	check_record_rdct(t_ms *minishell)
{
	int i;
	int	dest;

	dest = 0;
	i = 0;
	while (minishell->line[i])
	{
		if (*minishell->line[i] == '>' && minishell->line[i][1] != '>')
			dest = 112;
		else if (*minishell->line[i] == '>' && minishell->line[i][1] == '>')
			dest = 113;
		else if (*minishell->line[i] == '<'&& minishell->line[i][1] != '<')
			dest = 114;
		else if (*minishell->line[i] == '<' && minishell->line[i][1] == '<')
			dest = 115;
		i++;
		if (dest)
			break ;
	}
	return (dest);
}

char	*check_record_file(t_ms *minishell, int rc)
{
	int	i;
	char *line;

	i = 0;
	if (rc == 112)
	{
		while (*minishell->line[i] != '>')
			i++;
	}
	else if (rc == 113)
	{
		while (*minishell->line[i] != '>' && minishell->line[i][1] != '>')
			i++;
	}
	else if (rc == 114)
	{
		while (*minishell->line[i] != '<')
			i++;
	}
	else if (rc == 115)
	{
		while (*minishell->line[i] != '<' && minishell->line[i][1] != '<')
			i++;
	}
	i++;
	if (minishell->line[i])
		line = ft_strdup(minishell->line[i]);
	minishell->line = jopa(minishell, i);
	return(ft_strdup(line));
}

/*
RDCT_R 112 >
RDCT_RR 113 >>
RDCT_L 114 <
RDCT_LL 115 <<
*/