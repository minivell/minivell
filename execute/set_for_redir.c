#include "../minishell.h"

int	set_for_redir(t_exec *exec_info, t_redir *redir)
{
	t_redir	*node;

	if (redir == NULL)
		return (TRUE);
	node = redir;
	while (node)
	{
		if (node->type == IN_REDIR || node->type == HEREDOC)
		{
			exec_info->infile_fd = open(redir->filename, O_RDONLY);
			if (exec_info->infile_fd == FAILURE)
			{
				printf("error\n");
				return FALSE; // error
			}
			if (dup2(exec_info->infile_fd, STDIN_FILENO) == FAILURE)
			{
				printf("error\n");
				return FALSE; // error
			}
			close(exec_info->infile_fd);
		}
		else if (node->type == OUT_REDIR)
		{
			exec_info->outfile_fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (exec_info->outfile_fd == FAILURE)
				return FALSE; // error
			if (dup2(exec_info->outfile_fd, STDOUT_FILENO) == FAILURE)
				return FALSE; // error
			close(exec_info->outfile_fd);
		}
		else if (node->type == APPEND_REDIR)
		{
			exec_info->outfile_fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (exec_info->outfile_fd == FAILURE)
				return FALSE; // error
			if (dup2(exec_info->outfile_fd, STDOUT_FILENO) == FAILURE)
				return FALSE; // error
			close(exec_info->outfile_fd);
		}
		node = node->next;
	}
	return (TRUE);
}
