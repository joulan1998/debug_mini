/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yosabir <yosabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:29:24 by yosabir           #+#    #+#             */
/*   Updated: 2024/11/23 22:29:49 by yosabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <stdbool.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "libft.h"

typedef struct s_environ 
{
	char *var;
	char *value;
	struct s_environ *next;
	int exit_status;
} t_environ;

typedef struct set_list 
{
	int input;
	int output;
	char **args;
	struct set_list *next;
} set_args;

typedef enum s_type 
{
	BUILT_IN,
	SIMPLE_COMMAND,
} t_type;

typedef struct s_heredoc_info 
{
	char *file_name;
	int input;
} t_hdc;

typedef enum s_command 
{
	RD_IN,
	RD_OUT,
	APPEND,
	HEREDOC,
	S_QUOTE,
	D_QUOTE,
	PIPE,
	VAR,
	SPACEE,
	WORD,
} t_command;

typedef struct s_list 
{
	char *content;
	t_type type;
	t_command command;
	struct s_list *next;
	char **env;
	bool is_arg;
} t_list;



typedef enum e_tags {
	COMMAND_NOT_FOUND,
	TOO_MANY_ARGS,
	NUMRC_ARG_REQUIRED,
	PERM_ERROR,
	NOSUCHFORD,
} t_tags;

typedef enum e_no {
	ENO_SUCCESS,
	ENO_TOO_MANY_ARGS,
	ENO_GENERAL,
	ENO_CMMND_NT_FOND,
	ENO_CANT_EXEC = 126,
	ENO_EXEC_255 = 255,
} t_no;

typedef struct e_error {
	t_tags tag;
	t_no error_no;
	char *cause;
} t_error;

typedef struct s_minishell {
	char *line;
	char **env;
	t_environ *env_lst;
	// int exit_s;
	int status;
	int stdin;
	int stdout;
	char *old_path;
	set_args *commands;
	t_list *list;
} t_minishell;

// MINISHELL STRUCTURES AND ENUMERATIONS
#define PROMPT "minishell$ "
#define OWN_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin"

int g_signal;

// LIBFT FUNCTIONS
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strcmp(char *s1, char *s2);
char		**ft_split(char const *s, char c);
void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *chain, int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
char		*ft_strjoin(char const *s1, char const *s2);
int			is_number(char *str);
int			ft_atoi(const char *str);
size_t		ft_strlcpy(char *dst, const char *src, size_t len);
size_t		ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_itoa(int n);
void		ft_putchar_fd(char c, int fd);
char		*ft_strtrim(char const *s1, char const *set);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
int			ft_lstsize(t_environ *lst);


//////////////////////////////AEL-GARR/////////////////////////////////////////////////////////////
// FUNCTION PROTOTYPES
int			exec(t_minishell *data);
void		free_environment(char **env);
int			start_execution(t_minishell *data);
void		ctl_d_signal(int sig);
int			waitpid_fnc(t_minishell *data, int pid);
void		errno_handling(t_minishell *data, int *err, char *path);
int			initialize_fds(int ***table, int n);
void		close_fd(int *n);
int			dupping(int old, int new);
// BUILT-IN FUNCTION PROTOTYPES
int			ft_cd(t_minishell *data);
int			ft_echo(t_minishell *data);
int			ft_ls(t_minishell *data);
int			ft_env(t_minishell *data);
int			ft_error(char *first, t_tags message);
int			ft_exit(t_minishell *data);
int			to_alloc(char *s, char c);
int			ft_pwd(t_minishell *data);
int			final_update(t_minishell *data, char *key, char *value, bool create);
int			ft_export(t_minishell *data);
int			ft_error_export_2_args(char *fctn_name, char *command);
char		*extract_key(char *string);
int			check_syntax_for_export(char *string);
char		*extract_value(char *line);
int			ft_err_msg(t_error error);
int			print_export(t_minishell *data);
t_environ	*create_list(t_minishell *data);
t_environ	*ft_lstnew_env(char *var, char *value);
int			sort_and_print(char **table);
void		ft_lstadd_back_env(t_environ **lst, t_environ *new);
int			count_table_entries(char **table);
int			ft_unset(t_minishell *data);
char		*ft_find_node(t_minishell *data, char *str);
int			exec_smpl_cmnd(t_minishell *data);

// UTILITY FUNCTIONS
int			ft_free_table(char ***table);
int			free_table(t_minishell *data);
char		*joinning_and_free(char *s1, char *s2);
char		*check_acces(t_minishell *data, char *ftn);


// MULTI COMMAND FUNCTIONS
int			exe_commands(t_minishell *data);
int			multi_commands(t_minishell *data);
int			small_parse(t_minishell *data, char *cmd);

// SIGNAL FUNCTIONS
void		init_signl(int catch_signal);
void		ctrl_c_sig(int sig);

// MERGING FUNCTIONS
int			ft_lstsize_m(t_list *lst);
int			ft_lstsize_c(set_args *lst);

// TESTING FUNCTIONS
void		test_node_content(t_minishell *data);
void		test_list_content(t_minishell *data);
void		c_collector(t_minishell *data);
int			joinning_for_print(t_environ **node, char **list);

/////////////////////////////YOSABIIR//////////////////////////////////////////////////////////////
//  CLASSING FUNCTIONS PROTOTYPES
void		classing(t_list **lst);

// EXPANSION FUNCTIONS PROTOTYPES
t_list		*expanding(t_list *list, t_environ *env);
char		*expand_variable(t_list *token, t_environ *env);
char		*expand_double_q_variable(t_list *token, t_environ *env);
char		*expand_here_doc(char *string, int dont_expand, t_environ *env);
char		*extract_variable(char *s);
char		*get_variable_value(char *variable, t_environ *env);
char		*contact_varstr(char *string, char *variable);
int			get_variable_index(char *s);

// PARCING FUNCTION PROTOTYPES
t_list		*parsing(char *str, t_environ *env);
int			parse_variable(char *str, int i, t_list **lst, t_environ *env);
int			parse_word(char *str, int i, t_list **lst);
int			parse_spaces(char *str, int i, t_list **lst);
int			parse_quote(char *str, int i, t_list **lst);

//  SYNTAX FUNCTION PROTOTYPES
int			syntax(t_list **lst);
int			syntax_consecutive_redirection(t_list **lst);
int			syntax_end_of_command(t_list **lst);
int			syntax_redpipe(t_list **lst);
int			check_redirection_followed_by_pipe(t_list *lst);
int			check_consecutive_pipes(t_list *lst);
int			is_valid_next(t_list *token);
int			is_space(t_list *token);

// HANDLING FILES REDIRECTIONS
void		handle_red(t_list *token, set_args *cmd_args, t_environ *env);

// HANDLE HEREDOC FILE
t_hdc		open_create_herdoc_file(int i);
int			herdoc(int input, char *del, t_list *token, t_environ *env);

// SETTINGARGUMENTS LIST
set_args	*init_set_args(void);
set_args	*args(t_list **lst, t_environ *env, int num);
void		storing_args(t_list **current, set_args *cmd_args, t_environ *env);
void		process_argument(t_list **current, set_args *cmd_args);
char		*concatenate_args(t_list **current);
void		add_arg_to_set_args(set_args *cmd_args, char *new_arg);

// ERROR MESSAGE
void		error_message(t_list *lst, t_environ *env);

//  CLEARING LISTS
void		clear_env_list(t_environ *env_lst);
void		c_collector(t_minishell *data);
void		free_set_args(set_args *list);
void		free_t_list(t_list *list);

// PARSING UTILITIES
int			add_node_to_list(t_list **lst, char *substring, int cmd);
int			pipen(t_list **lst);
t_list		*skip_spaces(t_list *token);
int			is_special_char(char c);
int			get_special_char(char *str);
int			find(char *s, char sp);

#endif // MINISHELL_H
