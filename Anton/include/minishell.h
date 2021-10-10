/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:28:12 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/10 18:55:00 by ghumbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "..//libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>
# define MAX 1
# define MIN 0
# define RDCT_R 112
# define RDCT_RR 113
# define RDCT_L 114
# define RDCT_LL 115


typedef struct s_ms
{
    char *input;
    char **line;
    char **env;
    char **way;
	struct s_rdct *rdct;
} t_ms;

typedef struct s_cmd
{
	char *util_cmd; //* Утилита
	char **argv;	//* Здесь команда с аргументами или файл
	char *file;		//* Файл если был какой-нибудь редирект
	short operator; //* Здесь какой-либо оператор : < > << >> |
	struct s_cmd *next;
	struct s_rdct *rdct;
	struct s_cmd *back;
} t_cmd;

typedef struct s_env
{
	char *variable;
	char *value;
	struct s_env *next;
	struct s_env *back;
	struct s_env *next_alpha;
	struct s_env *back_alpha;
} t_env;

typedef struct s_rdct
{
	int heredoc[2];
	int rdct;
	struct s_rdct *next;
	struct s_rdct *back;
	char *file;
} t_rdct;


int		ft_strcmp(const char *s1, const char *s2);

/*readline*/
void 	rl_replace_line(const char *text, int clear_undo);
void 	rl_clear_history(void);

char 	**ft_argvdup(char **env);
int		overwrite_env(t_env **env, char *value, char *new_value);
char 	*name_of_variable(char *s);
char 	*value_of_variable(char *s);
void	alpha_variables (t_env *env);
t_env	*get_maxmin_variable (t_env *variable, _Bool min_max);

char 	**ft_envdup(char **env);
void	env_record(t_env **env, char **ev);
void 	env_value_add (t_env **lst, t_env *el);
t_env *new_env_value(char *varias);


void	pipes(t_cmd *cmd, int input, char **env, t_env **ev);

void	free_all(t_env **env);

/*builtin*/
void	ft_env(t_env *ev);
void	ft_echo(char **arg);
void	ft_cd(char *arg, t_env **env);
void    ft_pwd(t_env *env);
void	ft_unset (t_env **env, char **value);
void	ft_export(t_env **ev, char **arg);




int len_tab(char **str);
char **jopa(t_ms *minishell, int i);
char **record_cmd2(t_ms *minishell);
t_cmd *new_cmd(t_ms *minishell);
void lst_add (t_cmd **lst, t_cmd *el);
char *check_path(t_ms *minishell);
int		check_bin(t_ms *minishell);
void	null_struct(t_ms *minishell, char **ev);
char	**ft_split_for_minishell(char const *s, char c);
void	get_path(t_ms *minishell);
char	*right_way(t_ms *minishell);
char    *check_path_for_slash(t_ms *minishell, char **line);
char	*pwd_check(t_ms *minishell);
char	*slash_path(char *way, char *line);
int check_quote(t_ms *minishell);




// < > << >> 
void	record_cmd_rc(t_cmd **cmd, t_ms *minishell);
char	**record_cmd_rc_two(t_ms *minishell);
int	check_record_rdct(t_ms *minishell);
void	record_v_rdct(t_ms *minishell, int a);
void *new_rcdt(t_ms *minishell);
void lstadd_rdct(t_rdct **lst, t_rdct *el);
char	*check_record_file(t_ms *minishell, int rc);
void	record_cmd(t_cmd **cmd, t_ms *minishell, t_env **env, t_rdct **rdct);
#endif