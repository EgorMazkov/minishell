#include "../include/minishell.h"

int	rdct_right(t_cmd *cmd)
{
	int record = open(ft_split(cmd->file, ' ')[1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (record == -1)
	{
		perror(ft_split(cmd->file, ' ')[1]);
		exit(0);
	}
	dup2(record, 1);
	close(record);
	return (RDCT_R);
}

int	rdct_right_append(t_cmd *cmd)
{
	int record = open(ft_split(cmd->file, ' ')[1], O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (record == -1)
	{
		perror(ft_split(cmd->file, ' ')[1]);
		exit(0);
	}
	dup2(record, 1);
	close(record);
	return (RDCT_RR);
}


int	rdct_left_read(t_cmd *cmd)
{
	int record = open(ft_split(cmd->file, ' ')[1], O_RDONLY);
	if (record == -1)
	{
		perror(ft_split(cmd->file, ' ')[1]);
		exit(0);
	}
	dup2(record, 0);
	close(record);
	return (RDCT_L);
}

void	ctrl_wd(int signum)
{
	(void)signum;
	// g_param->ret = 130;
}

int	rdct_left_dock(t_cmd *cmd)
{
	char *input;
	int fd[2];
	int i;
	pipe(fd);
	void *sgnl;
	signal(SIGINT, ctrl_wd), signal(SIGQUIT, SIG_IGN);
	(sgnl = rl_getc_function);
	rl_getc_function = getc;
	while (1)
	{
		i = -1;
		input = readline("\033[1;34mheredocccc $> \033[0;29m");
		if (!input || !ft_strcmp(input, ft_split(cmd->file, ' ')[1]))
			break ;
		while (input[++i])
			write(fd[1], &input[i], 1);
		write(fd[1], "\n", 1);
	}
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	// signal(SIGINT, cmd_c);
	(rl_getc_function = sgnl), signal(SIGINT, cmd_c_fork);
	signal(SIGQUIT, SIG_IGN);
	return (RDCT_LL);
}