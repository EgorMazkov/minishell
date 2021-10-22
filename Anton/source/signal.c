/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 22:02:56 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/22 22:02:57 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cmd_c_sl(int signum)
{
	(void)signum;
	printf("Quit :3\n");
}

void	cmd_c_fork(int signum)
{
	(void)signum;
	g_exit = 130;
	write(1, "\n", 1);
}

void	cmd_c(int signum)
{
	(void)signum;
	g_exit = 1;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
