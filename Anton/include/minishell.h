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

typedef struct s_cmd
{
	char *util_cmd; //* Утилита
	char **argv;	//* Здесь команда с аргументами или файл
	char *file;		//* Файл если был какой-нибудь редирект
	short operator; //* Здесь какой-либо оператор : < > << >> |
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


typedef struct s_built
{
	char *oldpwd;
	char **env;
} t_built;



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
void	ft_env_add (t_built *lst, char *el);
void	env_record(t_env **env, char **ev);
void 	env_value_add (t_env **lst, t_env *el);
t_env *new_env_value(char *varias);


void	free_all(t_env **env);

/*builtin*/
void	ft_env(t_env *ev);
void	ft_echo(char **arg);
void	ft_cd(char *arg, t_env **env, t_built *old);
void    ft_pwd(char **env);
void	ft_unset (t_env **env, char **value);
void	ft_export(t_env **ev, char *arg);



#endif