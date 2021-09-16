/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:28:12 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/16 15:03:58 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "..//libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <readline/history.h>
#include <readline/readline.h>

typedef struct s_cmd
{
	char *util_cmd; //* Утилита
	char **argv;	//* Здесь команда с аргументами или файл
	char *file;		//* Файл если был какой-нибудь редирект
	short operator; //* Здесь какой-либо оператор : < > << >> |
} t_cmd;

/*readline*/
void rl_replace_line(const char *text, int clear_undo);
void rl_clear_history(void);

#endif