#include "../include/minishell.h"

void	free_argv (char **argv)
{
	int i;

	i = -1;
	if (argv && *argv != '\0')
	{
		if (*argv)
		while (argv[++i])
			free_str(argv[i]);
	}
	if (argv)
		free(argv);
}


void	free_str(char *string_free)
{
	if (string_free)
		free(string_free);
}


void	free_cmd(t_cmd **cmd)
{
	t_cmd *temp;

	while (cmd && *cmd && (*cmd)->back)
		*cmd = (*cmd)->back;
	while (*cmd)
	{
		temp = *cmd;
		*cmd = (*cmd)->next;
		free_argv(temp->argv);
		free_argv(temp->redicts);
		free(temp);
	}
}


void	free_env(t_env **env)
{
	t_env *temp;

	while ((*env)->back)
		*env = (*env)->back;
	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free_str(temp->variable);
		free_str(temp->value);
		free(temp);
	}		
}


void	free_minishell(t_ms *minishell)
{
	free_str(minishell->input);
	free_argv(minishell->env);
	free_argv(minishell->line);
	free_argv(minishell->way);
}



void	s(t_cmd **lst, t_cmd *el)
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



t_cmd	*cret(char *a)
{
	t_cmd	*el;
	int		j;

	j = 0;
	el = (t_cmd *)malloc(sizeof(t_cmd));
	if (!el)
		return (NULL);
	el->fd_her = -1;
	el->fd_read = -1;
	el->fd_write = -1;
	el->next = NULL;
	el->back = NULL;
	el->redicts = ft_split(a, ' ');
	el->argv = ft_split(a, ' ');
	return (el);
}




//int main ()
//{
//	t_cmd *r;
//	r = NULL;
//	int i = 0;
//	while (i++ != 1)
//		s(&r, cret("1 2 3 4 5 6   7  8   9"));
//	free_cmd(&r);
//	r = NULL;
//	if (!r)
//		printf("Complete!\n");
//	while (1);
//}