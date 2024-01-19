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
//		replace_env_in_line(&line, env); -> key로 value 찾는 함수 있나 경아한테 물어보기
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	// unlink(new_filename);
}

void	set_heredoc_filename(t_shell *shell_info)
{
	char	*new_filename;
	int		heredoc_filenum;
	t_cmd	*node;
	t_redir	*tmp_redir;

	heredoc_filenum = 0;
	node = shell_info->cmd;
	while (node)
	{
		tmp_redir = node->redir;
		while (tmp_redir)
		{
			if (tmp_redir->type == HEREDOC)
			{
				new_filename = ft_strjoin("heredoc_", \
				ft_itoa(heredoc_filenum));
				heredoc_filenum++;
				exec_heredoc(shell_info->env, new_filename, \
				tmp_redir->filename);
				free(tmp_redir->filename);
				tmp_redir->filename = new_filename;
			}
			tmp_redir = tmp_redir->next;
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
