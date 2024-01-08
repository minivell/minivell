#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define FAILURE -1

# define TRUE 1
# define FALSE 0

# define O_STREAM 1
# define I_STREAM 0


# include "struct.h"
# include "./libft/libft.h"


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include <readline/readline.h>
# include <readline/history.h>

/*parse*/

/*parse_all.c*/
int		parse_all(t_shell *shell_info, char *str);

/*init_env.c*/
void	init_env(t_env **env, char *envp[]);

/*parse_pipe.c*/
void 	parse_pipe(t_token **token, char *str);

/*parse_redir.c*/
void    parse_redir(t_token **token);
void    parse_and_extract_redir(t_token **token, char *str);
void    create_redir_token(t_token **token, char **str);

/*parse_space.c*/
int     ft_isspace(int c);
void 	parse_space(t_token **token);

/*cmd.c*/
// void    init_cmd(t_cmd **cmd, t_token *token);

/*redir.c*/
t_redir *new_redir(t_type type, char *filename);
void    add_back_redir(t_redir **redir, t_redir *new);
void    free_redir(t_redir *redir);

/*quote.c*/
int		check_quote(t_quote *quote, char c);

/*token.c*/
void	add_token_if_not_empty(char **start, char **current, t_token **token, t_type type);
t_token	*new_token(t_type type, char *value);
void	add_back_token(t_token **node, t_token *new);
void    replace_token(t_token **token_list, t_token *old_token, t_token *new_tokens);
void	free_token(t_token *token);

/* execute */

// [execute/execute.c]
int		execute(t_shell *shell_info);

// [execute/init_exec.c]
void	init_exec(t_shell *shell_info, t_exec *exec_info);
void	make_new_env(t_exec *exec_info);
char	**get_path(t_exec *exec_info);

// [execute/multi_process.c]
void	multi_process(t_shell *shell_info, t_exec *exec_info);
void	exec_child_process(t_exec *exec_info, t_cmd *cmd, int order, int last);
void	exec_parents_process(t_exec *exec_info);


// [execute/single_process.c]
int	single_process(t_shell *shell_info, t_exec *exec_info);
int	exec_cmd(char **cmd_arg, t_exec *exec_info);
char	*get_cmd_path(char *cmd, char **path);

// [builtin/check_n_exec_builtin.c]
int		check_n_exec_builtin(t_cmd *cmd_info);

#endif
