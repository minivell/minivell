#ifndef MINISHELL_H
# define MINISHELL_H

# include "struct.h"

# include <stdio.h>
# include <stdlib.h>

# include <readline/readline.h>
# include <readline/history.h>

/*parse*/
void	init_env(t_env **env, char *envp[]);

#endif
