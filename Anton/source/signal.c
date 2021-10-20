#include "../include/minishell.h"


void cmd_c_sl(int signum)
{
	(void)signum;
	printf("Quit :3\n");
}

void cmd_c_fork(int signum)
{
	(void)signum;
	// g_param->ret = 1;
	g_exit = 130;
	write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
}

void cmd_c(int signum)
{
	(void)signum;
	// g_param->ret = 1;
	g_exit = 1;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}