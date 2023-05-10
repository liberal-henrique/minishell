/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:54:04 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/10 19:20:51 by lliberal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include<unistd.h>
# include<stdlib.h>
# include<stdio.h>
# include<string.h>
# include<stddef.h>
# include<readline/readline.h>
# include<readline/history.h>

// Signal libraries
# include<signal.h>
# include<stdarg.h>
# include<sys/types.h>

# define STATUS_ERROR 1 //tmp
# define STATUS_SUCCESS 0

# define UNEXPECTED_TOKEN "bash: syntax error near unexpected token `|'"

typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;
typedef struct s_terminal	t_terminal;

struct s_terminal
{
	char			**env;
	char			**expo;
	char			*path;
	int				status;
	t_cmd			*begin;
};

struct s_cmd
{
	char			*str;
	char			**args;
	int				flag_quotes;
	char			*gpath;
	int				fd[2];
	int				pid;
	int				status;
	int				(*execute)(t_cmd *cmd, int in);
	t_cmd			*next;
};

void					sighandler();

//-----------parsing----------------------//
void					tokens(const char *line);
//path
char					*path_join(char *s1, char *s2);
char					*get_path(char **env);
char					*get_gpath(char **env, char **args);

//----------calloc-----//
void					*malloc_ob(size_t length);

//---------ft_replace---------------//
int						check_contain(char *origin, char *set);
int						contain_char(char *s, char c);
int						ft_compare(const char *s1, const char *s2);
char					*ft_replace(char *dst, char *to, char *rep);

//-----------ft_split---------//
char					**ft_split(char const *s, char c);
void					free_2d(char **result);
//----------ft_subtring--------//
char					*ft_substring(const char *str, int start, int end);

//----------helpers------//
int						is_quote(char c);
int						is_separator(const char *s, int *j);
int						is_space(char c);
void					put_str(char *s);

//----------linked_list----------//
int						cnt_rec(t_cmd *node);
void					deallocate(t_cmd *curr);
void					*get_function(char *name);
t_cmd					*insert_end(t_cmd **root, char *s, t_cmd *end);
void					print_linked(t_cmd *curr);

//----------utils----------//
size_t					ft_strlen(const char *a, char set);
char					*ft_strcpy(char *dest, char *src);
char					*ft_strcat(char *dest, char *src);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strdup(const char	*s1);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//          Execution

//----------Builtin----------------------//
int						execute_cd(t_cmd *cmd);
int						execute_echo(t_cmd *cmd);
int						execute_env(t_cmd *cmd);
int						execute_export(t_cmd *cmd);
int						execute_pwd(t_cmd *cmd);
int						execute_unset(t_cmd *cmd);

//-----------execute----------------------------//
int						execute_redirection_out(t_cmd *cmd);
int						execute_redirection_append_out(t_cmd *cmd);
int						execute_main(t_cmd *cmd, int in);
int						execute_default(t_cmd *cmd);
void					ft_wait(t_cmd *cmd);

// --------utils_exe---------------------//
void					clone_env(char **env);
char					**increase_env(char **env);
int						ft_strncmp(char *s1, char *s2, int n);
char					*str_join(char *old, char *seg, char c);

extern t_terminal			g_terminal;

#endif
