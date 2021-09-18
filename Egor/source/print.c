#include "../include/minishell.h"

void	print_mass(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
	{
		printf("av[%d] %s\n", i, cmd->argv[i]);
		i++;
	}
}