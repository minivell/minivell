#ifndef MINISHELL_H
#define MINISHELL_H

#define SUCCESS 0
#define FAILURE -1

#define DEFAULT   0
#define IGNORE    1
#define MINIVELL  2
#define HRD_CHILD 3

#define TRUE 1
#define FALSE 0

#define O_STREAM 1
#define I_STREAM 0

#include "struct.h"
#include "./libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/termios.h>
#include <sys/wait.h>
#include <sys/ioctl.h>
#include <readline/readline.h>
#include <readline/history.h>

extern int g_exit_code;




void free_str_arr(char **arr);


/*parse*/

/*parse_all.c*/
int parse_all(t_shell *shell_info, char *str);

/*init.c*/
void init_shell(t_shell *shell_info);

/*env.c*/
void init_env(t_env **env, char *envp[]);
void	env_add_back(t_env **env, t_env *new);
t_env	*new_env(char *key, char *value);

/*convert_env.c*/
void process_tokens(t_shell *shell_info, t_token *token);
void expand_env(t_token *token, t_env *env_var);
char *find_value(t_env *env_list, char *key, int *flag);
void replace_env_in_token(t_env *env_list, t_token *token);

/*parse_pipe.c*/
void parse_pipe(t_token **token, char *str);

/*parse_redir.c*/
void parse_redir(t_token **token);
void parse_filename(t_token **token);
void parse_and_extract_redir(t_token **token, char *str);
void create_redir_token(t_token **token, char **str);

/*parse_space.c*/
int ft_isspace(int c);
int is_space_outside_quotes(char c, t_quote quote);
void update_quote_flag(char c, t_quote *quote);
t_token *create_new_token(t_type type, char *start, char *end);
void tokenize_string(char *str, t_type type, t_token **new_token_list);
void parse_space(t_token **token);

/*parse_error.c*/
int print_error_msg(void);
int quote_error(char *str);
int token_error(t_token *token);

/*signal.c*/
void	set_signal(int sig_int, int sig_quit);

/*cmd.c*/
// void    init_cmd(t_cmd **cmd, t_token *token);
t_cmd *tokens_to_cmds(t_token *tokens);
void free_cmd_list(t_cmd *cmd);

/*redir.c*/
t_redir *new_redir(t_type type, char *filename);
void add_back_redir(t_redir **redir, t_redir *new);
void free_redir(t_redir *redir);

/*quote.c*/
int check_quote(t_quote *quote, char c);
// char *find_value(t_env *env_list, char *key);
void replace_env_in_token(t_env *env_list, t_token *token);
void remove_outer_quotes(t_token **token);

/*quote_check.c*/
int validate_token(t_token **token);

/*token.c*/
void add_token_if_not_empty(char **start, char **current, t_token **token, t_type type);
t_token *new_token(t_type type, char *value);
void add_back_token(t_token **node, t_token *new);
void replace_token(t_token **token_list, t_token *old_token, t_token *new_tokens);
void free_token(t_token *token);
void count_token_type(t_shell *shell_info, t_token *token);

void free_env_list(t_env *env);

char *ft_strjoin_free(char *s1, const char *s2);
char *find_key(char *value, int *i, int *start_idx);

/* execute */

// [execute/check_num.c]
int		check_num(char *str);

// [execute/error.c]
void	print_error_message(char *cmd, char *arg, char *msg);

// [execute/exec_cmd.c]
void	exec_cmd(t_cmd *cmd, t_exec *exec_info, int child);

// [execute/exec_process.c]
void	exec_parents_process(t_exec *exec_info);
void	exec_child_process(t_exec *exec_info, t_cmd *cmd, int order, int last_child);

// [execute/execute.c]
void	execute(t_shell *shell_info);

// [execute/get_cmd_path.c]
char	*get_cmd_path(char *cmd, char **path);

// [execute/get_path.c]
char	**get_path(void);

// [execute/init_exec.c]
t_exec 	*init_exec(t_shell *shell_info);

// [execute/make_new_env.c]
char	**make_new_env(t_exec *exec_info);

// [execute/multi_process.c]
void multi_process(t_shell *shell_info, t_exec *exec_info);
void exec_child_process(t_exec *exec_info, t_cmd *cmd, int order, int last);
void exec_parents_process(t_exec *exec_info);

// [execute/set_for_heredoc.c]
int	set_for_heredoc(t_shell *shell_info);

// [execute/single_process.c]
void	single_process(t_shell *shell_info, t_exec *exec_info);

// [execute/set_for_redir.c]
int	set_for_redir(t_exec *exec_info, t_redir *redir);

// [execute/unlink_heredoc.c]
void	unlink_heredoc(void);


/* builtin */

// [builtin/cd.c]
int	cd(char **args, t_exec *exec_info);

// [builtin/check_n_exec_builtin.c]
int	check_n_exec_builtin(t_cmd *cmd_info, t_exec *exec_info, int exit_flag);

// [builtin/echo.c]
int	echo(char **args);

// [builtin/env.c]
int	env(t_exec *exec_info, char **cmd_args);

// [builtin/exit.c]
int exit_shell(char **cmd_args, int exit_flag);

// [builtin/export.c]
int	export(t_exec *exec_info, char **args);

// [builtin/pwd.c]
int	pwd(void);

// [builtin/unset.c]
int	unset(t_exec *exec_info, char **args);

#endif
