#ifndef STRUCT_H
# define STRUCT_H

# include "./libft/libft.h"

# define TRUE 1
# define FALSE 0

typedef struct s_exec
{
	int		pipe[2];
	char	**new_envp;
}	t_exec;


#endif
