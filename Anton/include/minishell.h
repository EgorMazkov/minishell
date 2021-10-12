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
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/history.h>
#include <readline/readline.h>
# define MAX 1
# define MIN 0

# include "../readline/include/readline/readline.h"

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
} t_ms;

typedef struct s_cmd
{
	char *util_cmd; //* Утилита
	char **argv;	//* Здесь команда с аргументами или файл
	char *file;		//* Файл если был какой-нибудь редирект
	short operator; //* Здесь какой-либо оператор : < > << >> |
	int fd_her;
	struct s_cmd *next;
	struct s_cmd *back;
} t_cmd; //* Так же будет добавлен список редиректов, который будет сокращен до одного или двух листов : откуда читать и куда писать

typedef struct s_env
{
	char *variable;
	char *value;
	struct s_env *next;
	struct s_env *back;
	struct s_env *next_alpha;
	struct s_env *back_alpha;
} t_env;


typedef struct s_params
{
	int fd_read;
	int fd_write;
	int exit_code;
} t_params;


extern t_params *g_params;

typedef struct s_rdct
{
	int heredoc[2];
	short rdct;
	struct s_rdct *next;
	struct s_rdct *back;
	char *file;
} t_rdct;

void	ctrl_wd(int signum);

int		ft_strcmp(const char *s1, const char *s2);

/*readline*/
void 	rl_replace_line(const char *text, int clear_undo);
void 	rl_clear_history(void);

char 	**ft_argvdup(char **env);
char **env_from_lists (t_env *env);
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



void	cmd_c_fork(int signum);
void	cmd_c(int signum);
int	rdct_right(t_cmd *cmd);
int	rdct_right_append(t_cmd *cmd);
int	rdct_left_read(t_cmd *cmd);
int	rdct_left_dock(t_cmd *cmd);


void	free_all(t_env **env);

/*builtin*/
void	ft_env(t_env *ev);
void	ft_echo(char **arg);
int		ft_cd(char *arg, t_env **env);
int		ft_pwd(t_env *env);
void	ft_unset (t_env **env, char **value);
int		ft_export(t_env **ev, char **arg);
int	ft_exit (char **code);



int len_tab(char **str);
char **jopa(t_ms *minishell, int i);
char **record_cmd2(t_ms *minishell);
t_cmd *new_cmd(t_ms *minishell);
void lst_add (t_cmd **lst, t_cmd *el);
void	record_cmd(t_cmd **cmd, t_ms *minishell, t_env **env);
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



#endif