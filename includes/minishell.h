/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lliberal <lliberal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:54:04 by lliberal          #+#    #+#             */
/*   Updated: 2023/05/28 21:31:00 by lliberal         ###   ########.fr       */
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
# define STATUS_SYNTAX_ERROR 3
# define UNEXPECTED_TOKEN "bash: syntax error near unexpected token `|'"
# define H printf("HERE\n")
# define T printf("THERE\n")

typedef struct s_cmd		t_cmd;
typedef struct s_env		t_env;
typedef struct s_terminal	t_terminal;
typedef struct s_expo		t_expo;
typedef struct s_token		t_token;

struct s_terminal
{
	char			**env;
	t_expo			*expo;
	char			*path;
	int				status;
	t_cmd			*begin;
};

struct s_cmd
{
	char			*str;
	t_token			*tokens;
	char			**args;
	char			*gpath;
	int				fd_master[2];
	int				fd[2];
	int				pid;
	int				status;
	int				(*execute)(t_cmd *cmd, int in);
	t_cmd			*next;
};

struct s_expo
{
	char			*variable;
	char			*value;
	t_expo			*next;
};

struct s_token
{
	char			*str;
	t_token			*next;
};

void					sighandler();

//-----------parsing----------------------//
int						ft_phrases(const char *line);
t_cmd					*create_list_tokens(char **arr);
void					cmd_redirect(t_cmd *cmd);
void					clean_redirect_tokens(t_token **list);
char					*putraska(char *str);
char					*ft_strjoin_expansion(char *line, char *buf);
char					*ft_strjoin_char(char *line, char c);

//path
char					*path_join(char *s1, char *s2);
char					*get_path(char **env, char *str);
char					*get_gpath(char **env, char **args);

//-----------expander--------------------//
int						check(char c);
char					*expander(char *str);
void					expander_args(t_cmd *list);

//-----------tokens----------------------//
void					token_add_back(t_token **root, char *str);
void					token_remove(t_token **root, t_token *elem);
void					ft_tokens(t_token **token, char *phrase);
t_cmd					*insert_end_tokens(t_cmd **root, char *s, t_cmd *end);
void					token_print(t_token *curr);

//----------calloc-----//
void					*malloc_ob(size_t length);

//---------comands-----//
char					**create_array_cmds(t_token *list);
void					build_cmds_list(t_cmd **list);
void					cmd_redirect(t_cmd *cmd);
void					clean_redirect_tokens(t_token **list);

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
int						is_redirect(const char *s);
int						is_space(char c);
void					put_str(char *s);
int						ft_isalpha(char c);
int						ft_isnum(char c);

//----------linked_list----------//
int						cnt_rec(t_token *node);
void					deallocate(t_cmd *curr);
void					*get_function(char *name);
t_cmd					*insert_end(t_cmd **root, t_cmd *end);
void					insert_end_list(t_expo **root, char *value);
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
int						execute_dollar(t_cmd *cmd);
int						execute_exit(t_cmd *cmd);

//-----------execute----------------------------//
int						execute_redirection_out(t_cmd *cmd);
int						execute_redirection_append_out(t_cmd *cmd);
int						ft_heredoc(t_cmd *cmd, char *delimiter, \
char *buf, int len);
char					*ft_strjoin_rodraska(char *line, char *buf);
int						execute_main(t_cmd *cmd, int in, int out);
int						execute_geral(t_cmd *cmd, int in, int out);
int						execute_default(t_cmd *cmd);
void					ft_wait(t_cmd *cmd);
void					cleanall(t_cmd *list);

// --------utils_exe---------------------//
char					**clone_env(char **env);
char					**increase_env(char **env);
int						ft_strncmp(char *s1, char *s2, int n);
char					*str_join(char *old, char *seg, char c);
int						ft_strlen_2d(char **a);
char					*find_var(char *var);

void					print_list(t_expo *node);
void					print_list2(t_expo *node, t_cmd *cmd);
int						ft_strcmp(const char *s1, const char *s2);
void					swap_content(char **node, char **node1);
void					bubblesort(t_expo *root);
t_expo					*insert_end_expo_list(t_expo **root, \
char *s, t_expo **end);
t_expo					*create_expo(char **env);
char					**synchronize_env(char *cmd);
char					**synchronize_env_adding(char **env, char *cmd);
char					*put_quotes(char *str);
int						env_variable_replaced(char *cmd, int *flag);

extern t_terminal			g_terminal;

#endif
