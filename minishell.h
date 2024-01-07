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

int		check_quote(t_quote *quote, char c);

void	parse_redir(t_token **token);
void	parse_and_extract_redir(t_token **token, char *str);
void	replace_token(t_token **token_list, t_token *old_token, t_token *new_tokens);
void	identify_redir(t_token **token, char **str, char *start_str);
void create_redir_token(t_token **token, char **str);

void	add_token_if_not_empty(char **start, char **current, t_token **token, t_type type);
t_token	*new_token(t_type type, char *value);
void	add_back_token(t_token **node, t_token *new);
void	free_token(t_token *token);

int		parse_all(/*t_shell *shell_info, */char *str);

#endif
