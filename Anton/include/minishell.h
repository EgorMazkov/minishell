/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghumbert <ghumbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:28:12 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/21 20:19:31 by ghumbert         ###   ########.fr       */
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
#include <string.h>
#include <errno.h>
# include "../readline/include/readline/readline.h"
# define MAX 1
# define MIN 0


# define RDCT_R 112
# define RDCT_RR 113
# define RDCT_L 114
# define RDCT_LL 115
# define RDCT_ALL 100


typedef struct s_ms
{
    char *input;
    char **line;
    char **env;
    char **way;
} t_ms;

typedef struct s_cmd
{
	int fd_read;
	int fd_write;
	char **argv;	//* Здесь команда с аргументами или файл
	int fd_her;
	char **redicts;
	struct s_cmd *next;
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



typedef struct s_pipe
{
	int a[2];
	int b[2];
	int flag;
	int exit_builtin;
	int was_red;
	int len;
	int out;
	pid_t pid;
} t_pipe;


typedef struct g_parm
{
	int gexit;
	int fd0_copy;
	int fd1_copy;
} t_parm;

typedef struct s_dollar
{
	int	i;
	int	j;
	int a;
	int	flag;
}	t_dollar ;


extern t_parm g_parms;


void exec(t_cmd **cmd, t_ms *minishell, t_env **env);

int check_heredoc(t_cmd **cmd);
int run_heredoc(char **redict, t_cmd **cmd);
void cmd_run(t_cmd **cmd);

void three_hundred_bucks(t_cmd **cmd, t_env **env);

void	ctrl_wd(int signum);

int		ft_strcmp(const char *s1, const char *s2);

/*readline*/
void 	rl_replace_line(const char *text, int clear_undo);
void 	rl_clear_history(void);

char 	**ft_argvdup(char **env);
char **env_from_lists (t_env *env);
int	env_to_lists(t_env **env, char **ev);
int		overwrite_env(t_env **env, char *value, char *new_value);
char 	*name_of_variable(char *s);
char 	*value_of_variable(char *s);
void	alpha_variables (t_env *env);
t_env	*get_maxmin_variable (t_env *variable, _Bool min_max);

char 	**ft_envdup(char **env);
void	env_record(t_env **env, char **ev);
void 	env_value_add (t_env **lst, t_env *el);
t_env *new_env_value(char *varias);
char *get_variable_env(t_env *ev, char *str);

void	pipes(t_cmd *cmd, t_env **ev);
void pipe_child_process(t_cmd *cmd, t_env **ev, t_pipe *pip);
t_cmd *pipe_parent_process(t_cmd *cmd, t_pipe *pip);
int built_in_run (t_cmd *cmd, t_env **ev);
int is_builtin (char *command);

int lenlist (t_cmd *list);
void	cmd_c_fork(int signum);
void	cmd_c(int signum);
void cmd_c_sl(int signum);
int	rdct_right(t_cmd *cmd);
int	rdct_right_append(t_cmd *cmd);
int	rdct_left_read(t_cmd *cmd);
int	rdct_left_dock(t_cmd *cmd, char *stop);
int why_rdct(t_cmd *cmd);
int choose_reds(t_cmd **cmd);
int get_descriptor(char **redir, t_cmd *cmd);

void	free_all(t_env **env);

/*builtin*/
void	ft_env(t_env *ev);
void	ft_echo(char **arg);
int		ft_cd(char *arg, t_env **env);
int ft_cd_home(t_env **env, char *oldpath, char *temp);
int ft_cd_no_parse(char *arg, t_env **env, char *temp);
int		ft_pwd(t_env *env);
void	ft_unset (t_env **env, char **value);
int		ft_export(t_env **ev, char **arg);
int	ft_exit (char **code);


void	free_argv (char **argv);
void	free_str(char *string_free);
void	free_cmd(t_cmd **cmd);
void	free_env(t_env **env);
void	free_minishell(t_ms *minishell);


char**	record_redicts(char **argv);
char **rewrite_cmd(char **argv);
void	files_closes (t_cmd *cmd);

int rdct_r(char **redir, int str, t_cmd *cmd);
int rdct_rr(char **redir, int str, t_cmd *cmd);
int rdct_l(char **redir, int str, t_cmd *cmd);
int rdct_ll(char **redir, int str, t_cmd *cmd);


int if_not_new_value(t_env *temp);
int concat_or_overwrite(t_env *temp, int concat, char *new_value);
void	value_delete(t_env **env, char *value);
int lenlist_env (t_env *list);
int	export_compare_not_value(t_env **ev, char *s);
int args_valid(char *ar);
char *level_down(char *s);

void	ft_str_err(char *strerr);
t_env	*getback(t_env *temp);

int len_tab(char **str);
char **record_cmd2(t_ms *minishell);
t_cmd *new_cmd(t_ms *minishell);
void lst_add (t_cmd **lst, t_cmd *el);
void	record_cmd(t_cmd **cmd, t_ms *minishell, t_env **env);
char *check_path(t_ms *minishell);
void	path(t_cmd **cmd, t_ms *minishell);
int	check_bin(t_cmd *cmd);
char	*right_way(t_cmd *cmd, t_ms *minishell);
void	get_path(t_ms *minishell);
t_ms	*null_struct(void);
char	**ft_split_for_minishell(char const *s, char c);
char    *check_path_for_slash(t_ms *minishell, char **line);
char	*pwd_check(t_ms *minishell);
char	*slash_path(char *way, char *line);
void	preparser_dollar(t_cmd **cmd, t_ms *minishell);
void	record_dollar(t_cmd **cmd, int i, t_ms *minishell);
char	*dollar_tolower(char **dest);
void	get_path_dollar(t_cmd **cmd, int a, t_ms *minishell);



void	record_list_cmd(char *dest, char *line, t_cmd **cmd);
void	cmd_run(t_cmd **cmd);
int	check_next_cmd(t_cmd **cmd);
char	**record_redicts(char **argv);
char	**rewrite_cmd(char **argv);
int	redirect_count(char **argv);
void	record_cmd(t_cmd **cmd, t_ms *minishell, t_env **env);
void	record_cmd_pipe(t_cmd **cmd, t_ms *minishell);
char	**record_cmd2(t_ms *minishell);
int is_builtin (char *command);
char	*jango(char **j, size_t i);
size_t	schet(char const *s, char c);
size_t	len_word(const char *src, size_t start, char c);
char	**array_shift(t_ms *minishell, int i);
int	check_quote(t_ms *minishell);



void	trim(t_cmd **cmd, t_dollar *dollar);
void	trim_two(t_cmd **cmd, t_dollar *dollar, t_env **env);
int	check_dollar_null(t_cmd **cmd, t_dollar *dollar, t_env **env);
void		check_j(t_cmd **cmd, t_dollar *dollar, t_env **env);
void	torsion_cmd(t_cmd **cmd, t_dollar *dollar);
void	trimmer(t_cmd **cmd, t_dollar *dollar, t_env **env);
void	three_hundred_bucks_util(t_cmd **cmd, int i);
void	null_dollar(t_dollar *dollar);
char	**torsion_i(char const *s, char **mass, int i, t_dollar *dollar);
char	**ft_split_for_minishell(char const *s, char c);
// static char	**cikl(char const *s, char c, int i, char **mass);
int	chek_qoute(char const *s, int *i, int flag, char c);
size_t	cikl_two(char const *s, char c, int i, int flag);
size_t	cikl_three(char const *s, size_t i, char **mass, size_t word);
int	mass_word(char **mass, size_t word, char const *s, int i);
char	**record_mass(char const *s, char **mass, t_dollar *dollar, int *i);

int	validator(t_cmd *cmd);

int	valid_two(t_cmd **cmd, int *i);
int	val_three(t_cmd *cmd, int *i);
int	valid_four(t_cmd **cmd, int *i);
int	is_rdct(char *dest);
int	validator_pipe(t_ms *minishell);
void	dollar(t_cmd **cmd, t_env **env);



// test
void test(t_cmd **cmd);
#endif