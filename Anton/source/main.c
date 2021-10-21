#include "../include/minishell.h"

int g_exit;








void test(t_cmd **cmd)
{
	t_cmd *temp;
	int i = -1;
	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	temp = *cmd;
	while (temp)
	{
		while (temp->argv[++i])
			printf("%s\n", temp->argv[i]);
		i = -1;
		while (temp->redicts && temp->redicts[++i])
			printf("%s\n", temp->redicts[i]);
		printf("----------------((Anton))------------------\n");
		temp = temp->next;
		i = -1;
	}
}

int bucksonly(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] != '$')
			return (0);
	return (1);
}

void three_hundred_bucks(t_cmd **cmd, t_env **env)
{
	int i;
	char *temp;
	t_cmd *first_command;

	while ((*cmd)->back)
		*cmd = (*cmd)->back;
	first_command = *cmd;
	while (*cmd)
	{
		i = -1;
		if (!(*cmd)->argv || !(*cmd)->argv[0])
		{
			*cmd = (*cmd)->next;
			continue;
		}
		while ((*cmd)->argv[++i])
		{
			if ((*cmd)->argv[i][0] == '\'')
			{
				temp = (*cmd)->argv[i];
				(*cmd)->argv[i] = ft_strtrim((*cmd)->argv[i], "\'");
				free_str(temp);
			}
			else if ((*cmd)->argv[i][0] == '\"')
			{
				temp = (*cmd)->argv[i];
				(*cmd)->argv[i] = ft_strtrim((*cmd)->argv[i], "\"");
				free_str(temp);
			}
			if (!ft_strcmp((*cmd)->argv[i], "$?"))
			{
				temp = (*cmd)->argv[i];
				(*cmd)->argv[i] = ft_itoa(g_exit);
				free(temp);
				continue;
			}
			if ((*cmd)->argv[i][0] == '$')
			{
				temp = (*cmd)->argv[i];
				if (bucksonly(temp))
					break;
				(*cmd)->argv[i] = ft_strdup(get_variable_env(*env, (*cmd)->argv[i] + 1));
				// printf("%s\n", (*cmd)->argv[i]);
				free(temp);
			}
		}
		*cmd = (*cmd)->next;
	}
	*cmd = first_command;
}



void go_readline_go(t_cmd **cmd, t_ms *minishell, t_env **env)
{
	if (!minishell->input)
	{
		free_cmd(cmd);
		free_minishell(minishell);
		printf("exit\n");
		exit(0);
	}
	if (!check_quote(minishell))
	{
		printf("Error\n");
		return ;
	}
	if (*minishell->input)
		add_history(minishell->input);
	if (minishell->input[0])
	{
		minishell->line = ft_split_for_minishell(minishell->input, ' ');
		if (!*minishell->line)
			return ;
		if (!validator(minishell, 0))
			return ;
		exec(cmd, minishell, env);
		files_closes(*cmd);
		printf("\033[3;34mEXITCODE:    %d\n\033[0;29m", g_exit);
	}
}

int main(int argc, char **argv, char **ev)
{
	t_cmd *cmd;
	t_env *env;
	t_ms *minishell;

	(void)argc, (void)argv;
	// minishell = NULL;
	env = NULL;
	cmd = NULL;
	if (!env_to_lists(&env, ev))
		exit(1);
	while (1)
	{
		signal(SIGINT, cmd_c), signal(SIGQUIT, SIG_IGN);
		minishell = null_struct();
		minishell->input = readline("\033[0;32mDungeonMaster $> \033[0;29m");
		// minishell->input = ft_strdup("\"\"\"\"");
		signal(SIGINT, cmd_c_fork), signal(SIGQUIT, cmd_c_sl);
		go_readline_go(&cmd, minishell, &env);
		free_cmd(&cmd);
		free_minishell(minishell);
		free(minishell);
	}
	free_env(&env);
}
// export a+=b
//  fd = open("our way",  O_WRONLY | O_TRUNC | O_CREAT, 0666);
