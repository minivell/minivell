#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS 0
# define FAILURE -1

# define TRUE 1
# define FALSE 0

# include "struct.h"
# include "./libft/libft.h"


# include <stdio.h>
# include <stdlib.h>

# include <readline/readline.h>
# include <readline/history.h>

/*parse*/
void	init_env(t_env **env, char *envp[]);
void 	parse_pipe(t_token **token, char *str);
int		set_quote(t_quote *quote, char c);
void	add_token_if_not_empty(char **start, char **current, t_token **token, t_type type);
t_token	*token_new_node(t_type type, char *value);
void	token_add_back(t_token **node, t_token *new);
void	free_token(t_token *token);
int		parse_all(/*t_shell *shell_info, */char *str);

/* execute */
int		execute(t_shell *shell_info);
int		check_n_exec_builtin(t_cmd *cmd_info);
void	init_exec(t_shell *shell_info, t_exec *exec_info);




#endif
