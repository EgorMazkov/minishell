/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharodon <tharodon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:28:12 by ghumbert          #+#    #+#             */
/*   Updated: 2021/10/23 16:56:32 by tharodon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <string.h>
# include <errno.h>
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
	char	*input;
	char	**line;
	char	**env;
	char	**way;
}	t_ms;

typedef struct s_cmd
{
	int				fd_read;
	int				fd_write;
	int				fd_her;
	char			**argv;
	char			**redicts;
	struct s_cmd	*next;
	struct s_cmd	*back;
}	t_cmd;

typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
	struct s_env	*back;
	struct s_env	*next_alpha;
	struct s_env	*back_alpha;
}	t_env;

typedef struct s_pipe
{
	int		a[2];
	int		b[2];
	int		flag;
	int		exit_builtin;
	int		was_red;
	int		len;
	int		out;
	pid_t	pid;
}	t_pipe;

typedef struct g_parm
{
	int	gexit;
	int	fd0_copy;
	int	fd1_copy;
}	t_parm;

typedef struct s_dollar
{
	int		i;
	int		j;
	int		a;
	int		flag;
}	t_dollar;

extern t_parm	g_parms;

/*readline*/
int		env_to_lists(t_env **env, char **ev);
int		overwrite_env(t_env **env, char *value, char *new_value);
char	**ft_argvdup(char **env);
char	*name_of_variable(char *s);
char	*value_of_variable(char *s);
char	**env_from_lists(t_env *env);
void	rl_clear_history(void);
void	alpha_variables(t_env *env);
void	rl_replace_line(const char *text, int clear_undo);
t_env	*get_maxmin_variable(t_env *variable, _Bool min_max);

//parser

//path
char	*slash_path(char *way, char *line);
char	*right_way(t_cmd *cmd, t_ms *minishell);
void	get_path(t_ms *minishell);
void	path(t_cmd **cmd, t_ms *minishell);
void	path_way(t_ms *minishell, t_cmd **cmd, char *dest);

//record_cmd
char	**record_cmd2(t_ms *minishell);
void	record_cmd_pipe(t_cmd **cmd, t_ms *minishell);
void	record_cmd(t_cmd **cmd, t_ms *minishell, t_env **env);

//split_for_castom
int		chek_qoute(char const *s, int *i, int flag, char c);
int		mass_word(char **mass, size_t word, char const *s, int i);
char	*jango(char **j, size_t i);
char	**ft_split_for_minishell(char const *s, char c);
char	**torsion_i(char const *s, char **mass, int i, t_dollar *dollar);
char	**record_mass(char const *s, char **mass, t_dollar *dollar, int *i);
size_t	schet(char const *s, char c);
size_t	len_word(const char *src, size_t start, char c);
size_t	cikl_two(char const *s, char c, int i, int flag);
size_t	schet_two(char const *s, size_t i, size_t sep, char c);
size_t	cikl_three(char const *s, size_t i, char **mass, size_t word);

//validator
int		validator(t_cmd *cmd);
int		validator_pipe(t_ms *minishell);
int		is_rdct(char *dest);
int		valid_two(t_cmd **cmd, int *i);
int		val_three(t_cmd *cmd, int *i);
int		valid_four(t_cmd **cmd, int *i);

//utils
int		len_tab(char **str);
int		check_next_cmd(t_cmd **cmd);
int		check_quote(t_ms *minishell);
void	lst_add(t_cmd **lst, t_cmd *el);
void	dollar(t_cmd **cmd, t_env **env);
void	exec(t_cmd **cmd, t_ms *minishell, t_env **env);
void	record_list_cmd(char *dest, char *line, t_cmd **cmd);
char	**array_shift(t_ms *minishell, int i);
t_ms	*null_struct(void);
t_cmd	*new_cmd(t_ms *minishell);

/* logics */

//ajaraguju
int		built_in_run(t_cmd *cmd, t_env **ev);
void	cmd_run(t_cmd **cmd);
void	ft_str_err(char *strerr);

//built_in
int		args_valid(char *ar);
int		is_builtin(char *command);
int		export_compare_not_value(char *s);
char	*level_down(char *s);
char	*get_variable_env(t_env *ev, char *str);

//cd
int		ft_cd(char *arg, t_env **env);
int		ft_cd_no_args(t_env **env, char *temp);
int		ft_cd_tild(char *arg, t_env **env, char *temp);
int		ft_cd_home(t_env **env, char *oldpath, char *temp);
int		ft_cd_no_parse(char *arg, t_env **env, char *temp);
int		ft_cd_tild_util(char *arg, t_env **env, char *temp);

//echo
void	ft_echo(char **arg);
int		is_slash_n(char **str);

//env
int		lenlist(t_cmd *list);
int		lenlist_env(t_env *list);
int		if_not_new_value(t_env *temp);
int		env_to_lists(t_env **env, char **ev);
int		overwrite_env(t_env **env, char *variable, char *new_value);
int		concat_or_overwrite(t_env *temp, int concat, char *new_value);
char	*name_of_variable(char *s);
char	*value_of_variable(char *s);
char	**env_from_lists(t_env *env);
char	*value_of_env(t_env *env, char *value);
void	ft_env(t_env *ev);
void	env_record(t_env **env, char **ev);
void	env_value_add(t_env **lst, t_env *el);
t_env	*getback(t_env *temp);
t_env	*new_env_value(char *varias);

//exist
int		ft_exit(char **code);
int		len_argvs(char **ar);
int		is_numbers_to_string(char *str);
int		is_numbers_to_arguments(char **str);

// export
int		ft_export(t_env **ev, char **arg);

//free
void	free_env(t_env **env);
void	free_cmd(t_cmd **cmd);
void	free_argv(char **argv);
void	free_str(char *string_free);
void	free_minishell(t_ms *minishell);

//ganv
int		check_dollar_null(t_cmd **cmd, t_dollar *dollar, t_env **env);
void	trim(t_cmd **cmd, t_dollar *dollar);
void	torsion_cmd(t_cmd **cmd, t_dollar *dollar);
void	check_j(t_cmd **cmd, t_dollar *dollar, t_env **env);
void	trimmer(t_cmd **cmd, t_dollar *dollar, t_env **env);
void	trim_two(t_cmd **cmd, t_dollar *dollar, t_env **env);

//main
void	go_readline_go(t_cmd **cmd, t_ms *minishell, t_env **env);

//name_
int		warning_exit(void);
int		parser_and_validator(t_cmd **cmd, t_ms *minishell, t_env **env);
void	null_dollar(t_dollar *dollar);
void	swapping_fd(int fd0_copy, int fd1_copy);
void	run_bash_command_from_exec(t_cmd **cmd, t_env **env);

//open_files
int		rdct_l(char **redir, int str, t_cmd *cmd);
int		rdct_r(char **redir, int str, t_cmd *cmd);
int		rdct_rr(char **redir, int str, t_cmd *cmd);
int		rdct_ll(char **redir, int str, t_cmd *cmd);

//parenspipe
void	redirects_close(t_cmd *cmd, t_pipe *pip);
t_cmd	*pipe_parent_process(t_cmd *cmd, t_pipe *pip);

//parse_redirects
int		redirect_count(char **argv);
int		get_descriptor(char **redir, t_cmd *cmd);
int		get_descriptor_util(char **redir, int str, t_cmd *cmd);
char	**rewrite_cmd(char **argv);
char	**record_redicts(char **argv);
char	*space_between_redirect_and_file(char *input);

// pipe
int		first_command(t_pipe *pip);
void	crush_fork(t_pipe *pip);
void	mid_command(t_pipe *pip);
void	last_command(t_pipe *pip);
void	pipes(t_cmd *cmd, t_env **ev);
void	pipe_child_process(t_cmd *cmd, t_env **ev, t_pipe *pip);
t_cmd	*go_back_cmd(t_cmd *cmd);

//progress_bucksess
void	bucks(t_cmd **cmd, t_env **env);
void	three_hundred_bucks_util(t_cmd **cmd, int i);
void	three_hundred_bucks(t_cmd **cmd, t_env **env);

//pwd
int		ft_pwd(t_env *env);

//redict_utils
int		why_rdct(t_cmd *cmd);
int		choose_reds(t_cmd **cmd);
int		check_heredoc(t_cmd **cmd);
int		run_heredoc(char **redict, t_cmd **cmd);
int		value_redirect_why_rdct(int read, int write);

//redirects
int		rdct_left_dock(t_cmd *cmd, char *stop);
void	ctrl_wd(int signum);
void	files_closes(t_cmd *cmd);
void	loop_recording(char *stop, t_pipe pip);
void	wait_input_and_record(t_cmd *cmd, t_pipe pip);

//signal
void	cmd_c(int signum);
void	cmd_c_sl(int signum);
void	cmd_c_fork(int signum);

//sord_env
int		ft_strcmp(const char *s1, const char *s2);
void	alpha_variables(t_env *env);
t_env	*get_up_neighbour(t_env *el);
t_env	*get_maxmin_variable(t_env *variable, _Bool min_max);

//unset
void	null_env(t_env **del);
void	ft_unset(t_env **env, char **value);
void	value_delete(t_env **env, char *value);
void	cut_and_free_varias(t_env **env, t_env *temp);

#endif