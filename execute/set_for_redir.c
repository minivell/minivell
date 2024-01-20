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
				ft_putstr_fd("minivell: ", STDERR_FILENO);
				ft_putstr_fd(node->filename, STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
				exit(g_exit_code);
//				return FALSE; // error
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
			exec_info->outfile_fd = open(node->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (exec_info->outfile_fd == FAILURE)
			{
				ft_putchar_fd('1', STDERR_FILENO);
				return FALSE; // error
			}
			if (dup2(exec_info->outfile_fd, STDOUT_FILENO) == FAILURE)
			{
				ft_putchar_fd('2', STDERR_FILENO);
				return FALSE; // error
			}
			close(exec_info->outfile_fd);
		}
		else if (node->type == APPEND_REDIR)
		{
			exec_info->outfile_fd = open(node->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (exec_info->outfile_fd == FAILURE) {
				ft_putchar_fd('3', STDERR_FILENO);
				return FALSE; // error
			}
			if (dup2(exec_info->outfile_fd, STDOUT_FILENO) == FAILURE) {
				ft_putchar_fd('4', STDERR_FILENO);
				return FALSE; // error
			}
			close(exec_info->outfile_fd);
		}
		node = node->next;
	}
	return (TRUE);
}
