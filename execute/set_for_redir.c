#include "../minishell.h"

void	set_for_redir(t_exec *exec_info, t_redir *redir)
{
	t_redir	*node;

	if (redir == NULL)
		return ;
	node = redir;
	while (node)
	{
		if (node->type == IN_REDIR)
		{
			exec_info->infile_fd = open(redir->filename, O_RDONLY);
			if (exec_info->infile_fd < 0)
				return ; // error
			if (dup2(exec_info->infile_fd, STDIN_FILENO) < 0)
				return ; // error
			close(exec_info->infile_fd);
		}
		else if (node->type == HEREDOC)
		{
			printf("HEREDOC\n");
		}
		else if (node->type == OUT_REDIR)
		{
			exec_info->outfile_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (exec_info->outfile_fd < 0)
				return ; // error
			if (dup2(exec_info->outfile_fd, STDOUT_FILENO) < 0)
				return ; // error
			close(exec_info->outfile_fd);
		}
		else if (node->type == APPEND_REDIR)
		{
			exec_info->outfile_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (exec_info->outfile_fd < 0)
				return ; // error
			if (dup2(exec_info->outfile_fd, STDOUT_FILENO) < 0)
				return ; // error
			close(exec_info->outfile_fd);
		}
		node = node->next;
	}
}