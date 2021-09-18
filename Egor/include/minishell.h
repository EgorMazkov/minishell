/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:28:12 by ghumbert          #+#    #+#             */
/*   Updated: 2021/09/18 18:18:22 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "..//libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_ms
{
    char *input;
    char **line;
    int i;
    int argc;
    char **argv;
    char **env;
    char **way;
} t_ms;

typedef struct s_cmd
{
    char *util_cmd;//* Утилита
    char **argv;//* Здесь команда с аргументами или файл
    char *file;//* Файл если был какой-нибудь редирект
    short operator;//* Здесь какой-либо оператор : < > << >> |
} t_cmd;

void	null_struct(t_ms *minishell, t_cmd *cmd);
void	get_path(t_ms *minishell, char **ev);
char	*slash_path(char *way, char *line);
char	*right_way(t_ms *minishell);
void	appropriation(int argc, char **argv, char **ev, t_ms *minishell);
void	write_to_array(t_cmd *cmd, t_ms *minishell);
void	parser(t_ms *minishell, int i);


/*printf*/
void	print_mass(t_cmd *cmd);


/*readline*/
void	rl_replace_line(const char *text, int clear_undo);
void	rl_clear_history(void);





char    *trimmer(char *str, char c);
#endif