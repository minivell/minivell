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
void	init_env(t_env **env, char *envp[]);
void 	parse_pipe(t_token **token, char *str);

int		check_quote(t_quote *quote, char c);

void	parse_redir(t_token **token);
void	parse_and_extract_redir(t_token **token, char *str);
void	replace_token(t_token **token_list, t_token *old_token, t_token *new_tokens);
void 	create_redir_token(t_token **token, char **str);

void	add_token_if_not_empty(char **start, char **current, t_token **token, t_type type);
t_token	*new_token(t_type type, char *value);
void	add_back_token(t_token **node, t_token *new);
void	free_token(t_token *token);

void 	parse_space(t_token **token);

int		parse_all(/*t_shell *shell_info, */char *str);

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
