#ifndef STRUCT_H
# define STRUCT_H

# include "./libft/libft.h"

// share
typedef enum e_type
{
	WORD = 1,
	PIPE,
	FILENAME,
	OUT_REDIR,
	IN_REDIR,
	APPEND_REDIR,
	HEREDOC
}	t_type;

typedef struct s_shell
{
	int				pipe_cnt;
	int				heredoc_cnt;
	struct s_env	*env;
	struct s_cmd	*cmd;
}	t_shell;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// parse
typedef struct s_redir
{
	t_type			type;
	char			*filename;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	int				cmd_cnt;
	char			**cmd_args;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_quote
{
	int		quote_flag;
	char	quote;
}	t_quote;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_env_process 
{
	char	*str;
	int		*i;
	char	**res;
	int		*start_idx;
} t_env_process;

typedef struct s_index 
{
	int current;
	int start;
}	t_index;

// execute
typedef struct s_exec
{
	int 	infile_fd;
	int		outfile_fd;
	int		pipe[2];
	char	**path;
	t_env	*env;
}	t_exec;

#endif
