#include "../minishell.h"

//void	replace_env_in_line(t_env *env, char  *line)
//{
//
//}

void	exec_heredoc(t_env *env, char *new_filename, char *limiter)
{
	int		fd;
	char	*line;

	(void)env;
	fd = open(new_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == FAILURE) {
		perror("open failed\n");
		exit(EXIT_FAILURE); }
	while (TRUE)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
//		replace_env_in_line(&line, env);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	unlink(new_filename);
}

void	set_heredoc_filename(t_shell *shell_info)
{
	char	*new_filename;
	int		heredoc_filenum;
	t_cmd	*node;

	heredoc_filenum = 0;
	node = shell_info->cmd;
	while (node)
	{
		while (node->redir)
		{
			if (node->redir->type == HEREDOC)
			{
				new_filename = ft_strjoin("heredoc_", \
				ft_itoa(heredoc_filenum));
				heredoc_filenum++;
				exec_heredoc(shell_info->env, new_filename, \
				node->redir->filename);
				free(node->redir->filename);
				node->redir->filename = new_filename;
			}
			node->redir = node->redir->next;
		}
		node = node->next;
	}
}

void	set_for_heredoc(t_shell *shell_info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == FAILURE)
		exit(EXIT_FAILURE);
	else if (pid == SUCCESS)
		set_heredoc_filename(shell_info);
	wait(&status);
	if (WEXITSTATUS(status) == EXIT_FAILURE)
		g_exit_code = EXIT_FAILURE;
}

int	execute(t_shell *shell_info)
{
	int		origin_stdin;
	int		origin_stdout;
	t_exec *exec_info;

	exec_info = init_exec(shell_info);
	if (shell_info->heredoc_cnt != 0)
		set_for_heredoc(shell_info);
	origin_stdin = dup(STDIN_FILENO);
	origin_stdout = dup(STDOUT_FILENO);
	if (shell_info->pipe_cnt == 0)
		single_process(shell_info, exec_info);
	else
		multi_process(shell_info, exec_info);
	dup2(origin_stdin, STDIN_FILENO);
	dup2(origin_stdout, STDOUT_FILENO);
	return (SUCCESS);
}