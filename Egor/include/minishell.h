/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:28:12 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/02 16:12:25 by ghumbert         ###   ########.fr       */
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
    char **env;
    char **way;
    // char **way;
} t_ms;

typedef struct s_cmd
{
    char *util_cmd;//* Утилита
    char **argv;//* Здесь команда с аргументами или файл
    char *file;//* Файл если был какой-нибудь редирект
    short operator;//* Здесь какой-либо оператор : < > << >> |
    struct s_cmd *next;
	struct s_cmd *back;
} t_cmd;

int len_tab(char **str);
char **jopa(t_ms *minishell, int i);
char **record_cmd2(t_ms *minishell);
t_cmd *new_cmd(t_ms *minishell);
void lst_add (t_cmd **lst, t_cmd *el);
void	record_cmd(t_cmd **cmd, t_ms *minishell);
char *check_path(t_ms *minishell);
int		check_bin(t_ms *minishell);
void	null_struct(t_ms *minishell, char **ev);
char	**ft_split_for_minishell(char const *s, char c);
void	get_path(t_ms *minishell);
char	*right_way(t_ms *minishell);
char    *check_path_for_slash(t_ms *minishell, char **line);
char	*pwd_check(t_ms *minishell);
char	*slash_path(char *way, char *line);
#endif