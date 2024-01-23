/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 13:53:08 by gykoh             #+#    #+#             */
/*   Updated: 2024/01/23 18:35:17 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_convert_env
{
	int		start_idx;
	int		free_flag;
	char	quote_flag;
	char	*res;
	char	*temp;
	char	*key;
	char	*env_value;
}	t_convert_env;

// execute
typedef struct s_exec
{
	int		infile_fd;
	int		outfile_fd;
	int		pipe[2];
	char	**path;
	t_env	**env;
}	t_exec;

#endif
