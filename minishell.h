#ifndef MINISHELL_H
#define MINISHELL_H

#define EXIT_FAILURE 1
#define SUCCESS 0
#define FAILURE -1

#define TRUE 1
#define FALSE 0

#define O_STREAM 1
#define I_STREAM 0

#include "struct.h"
#include "./libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <readline/readline.h>
#include <readline/history.h>

extern int g_exit_code;

/*parse*/

/*parse_all.c*/
int parse_all(t_shell *shell_info, char *str);

/*init.c*/
void init_shell(t_shell *shell_info);

/*env.c*/
void init_env(t_env **env, char *envp[]);

/*parse_pipe.c*/
void parse_pipe(t_token **token, char *str);

/*parse_redir.c*/
void parse_redir(t_token **token);
void parse_filename(t_token **token);
void parse_and_extract_redir(t_token **token, char *str);
void create_redir_token(t_token **token, char **str);

/*parse_space.c*/
int ft_isspace(int c);
void parse_space(t_token **token);

/*parse_error.c*/
int error_before_parse(t_token *token, char *str);
int print_error_msg(void);
int quote_error(char *str);
int token_error(t_token *token);

/*cmd.c*/
// void    init_cmd(t_cmd **cmd, t_token *token);
t_cmd *tokens_to_cmds(t_token *tokens);

/*redir.c*/
t_redir *new_redir(t_type type, char *filename);
void add_back_redir(t_redir **redir, t_redir *new);
void free_redir(t_redir *redir);

/*quote.c*/
int check_quote(t_quote *quote, char c);
void remove_outer_quotes(t_token **token);

/*token.c*/
void add_token_if_not_empty(char **start, char **current, t_token **token, t_type type);
t_token *new_token(t_type type, char *value);
void add_back_token(t_token **node, t_token *new);
void replace_token(t_token **token_list, t_token *old_token, t_token *new_tokens);
void free_token(t_token *token);
void count_token_type(t_shell *shell_info, t_token *token);

/* execute */

// [execute/exec_cmd.c]
int	exec_cmd(char **cmd_args, t_exec *exec_info);

// [execute/exec_process.c]
void	exec_parents_process(t_exec *exec_info);
void	exec_child_process(t_exec *exec_info, t_cmd *cmd, int order, int last_child);

// [execute/execute.c]
int execute(t_shell *shell_info);

// [execute/get_cmd_path.c]
char	*get_cmd_path(char *cmd, char **path);

// [execute/get_path.c]
char	**get_path(t_exec *exec_info);

// [execute/init_exec.c]
t_exec 	*init_exec(t_shell *shell_info);

// [execute/make_new_env.c]
char	**make_new_env(t_exec *exec_info);


// [execute/multi_process.c]
void multi_process(t_shell *shell_info, t_exec *exec_info);
void exec_child_process(t_exec *exec_info, t_cmd *cmd, int order, int last);
void exec_parents_process(t_exec *exec_info);

// [execute/single_process.c]
void	single_process(t_shell *shell_info, t_exec *exec_info);
int		exec_cmd(char **cmd_args, t_exec *exec_info);
char	*get_cmd_path(char *cmd, char **path);
void	set_for_redir(t_exec *exec_info, t_redir *redir);


// [builtin/check_n_exec_builtin.c]
int check_n_exec_builtin(t_cmd *cmd_info);

// [builtin/echo.c]
//int	echo(char **args);
char	**make_new_env(t_exec *exec_info);


#endif
