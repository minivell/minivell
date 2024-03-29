/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_for_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eushin <eushin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:14:29 by eushin            #+#    #+#             */
/*   Updated: 2024/01/23 14:28:04 by eushin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	append_redir(t_exec *exec_info, t_redir *node)
{
	exec_info->outfile_fd = open(node->filename, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (exec_info->outfile_fd == FAILURE)
	{
		perror("open");
		exit (EXIT_FAILURE);
	}
	if (dup2(exec_info->outfile_fd, STDOUT_FILENO) == FAILURE)
	{
		perror("dup2");
		exit (EXIT_FAILURE);
	}
	close(exec_info->outfile_fd);
}

static void	outdir(t_exec *exec_info, t_redir *node)
{
	exec_info->outfile_fd = open(node->filename, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (exec_info->outfile_fd == FAILURE)
	{
		perror("open");
		exit (EXIT_FAILURE);
	}
	if (dup2(exec_info->outfile_fd, STDOUT_FILENO) == FAILURE)
	{
		perror("dup2");
		exit (EXIT_FAILURE);
	}
	close(exec_info->outfile_fd);
}

static int	indir_n_heredoc(t_exec *exec_info, t_redir *node)
{
	exec_info->infile_fd = open(node->filename, O_RDONLY);
	if (exec_info->infile_fd == FAILURE)
	{
		g_exit_code = 1;
		print_error_message(node->filename, NULL, "No such file or directory", \
			g_exit_code);
		return (FAILURE);
	}
	if (dup2(exec_info->infile_fd, STDIN_FILENO) == FAILURE)
	{
		perror("dup2");
		exit (EXIT_FAILURE);
	}
	close(exec_info->infile_fd);
	return (SUCCESS);
}

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
			if (indir_n_heredoc(exec_info, node) == FAILURE)
				return (FALSE);
		}
		else if (node->type == OUT_REDIR)
			outdir(exec_info, node);
		else if (node->type == APPEND_REDIR)
			append_redir(exec_info, node);
		node = node->next;
	}
	return (TRUE);
}
