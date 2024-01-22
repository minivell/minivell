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
			exec_info->infile_fd = open(node->filename, O_RDONLY);
			if (exec_info->infile_fd == FAILURE)
			{
				g_exit_code = 1;
				print_error_message(node->filename, NULL, "No such file or directory");
				return (FALSE);
			}
			if (dup2(exec_info->infile_fd, STDIN_FILENO) == FAILURE)
			{
				perror("dup2");
				return FALSE; // error
			}
			close(exec_info->infile_fd);
		}
		else if (node->type == OUT_REDIR)
		{
			exec_info->outfile_fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (exec_info->outfile_fd == FAILURE)
			{
				perror("open");
				return (FALSE);
			}
			if (dup2(exec_info->outfile_fd, STDOUT_FILENO) == FAILURE)
			{
				perror("dup2");
				return (FALSE);
			}
			close(exec_info->outfile_fd);
		}
		else if (node->type == APPEND_REDIR)
		{
			exec_info->outfile_fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (exec_info->outfile_fd == FAILURE)
			{
				perror("open");
				return FALSE; // error
			}
			if (dup2(exec_info->outfile_fd, STDOUT_FILENO) == FAILURE)
			{
				perror("dup2");
				return FALSE; // error
			}
			close(exec_info->outfile_fd);
		}
		node = node->next;
	}
	return (TRUE);
}
