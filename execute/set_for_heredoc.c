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
}

void	replace_new_filename(t_cmd *node, char *new_filename)
{
	t_redir	*tmp_redir;

	tmp_redir = node->redir;
	while (tmp_redir != NULL)
	{
		if (tmp_redir->type == HEREDOC)
		{
			free(tmp_redir->filename);
			tmp_redir->filename = new_filename;
		}
		tmp_redir = tmp_redir->next;
	}
}

void	set_heredoc_filename(t_shell *shell_info)
{
	char	*new_filename;
	int		num;
	t_cmd	*node;
	t_redir	*tmp_redir;
	char *n;

	set_signal(HRD_CHILD, HRD_CHILD);
	num = 0;
	node = shell_info->cmd;
	while (node != NULL)
	{
		tmp_redir = node->redir;
		while (tmp_redir != NULL)
		{
			if (tmp_redir->type == HEREDOC)
			{
				n = ft_itoa(num);
				new_filename = ft_strjoin("hrd_", n);
				num++;
				exec_heredoc(shell_info->env, new_filename, \
				tmp_redir->filename);
				tmp_redir->filename = new_filename;
				free(n);
			}
			tmp_redir = tmp_redir->next;
		}
		node = node->next;
	}
	 exit(EXIT_SUCCESS);
}

int	set_for_heredoc(t_shell *shell_info)
{
	pid_t	pid;
	int		status;

	set_signal(IGNORE, IGNORE);
	pid = fork();
	if (pid == FAILURE)
		exit(EXIT_FAILURE);
	else if (pid == SUCCESS)
		set_heredoc_filename(shell_info);
	wait(&status);
	if (WEXITSTATUS(status) == EXIT_FAILURE)
		g_exit_code = EXIT_FAILURE;
	set_signal(HRD_IGN, HRD_IGN);
	char	*new_filename;
	int		num;
	t_cmd	*node;
	t_redir	*tmp_redir;
	char *n;

	num = 0;
	node = shell_info->cmd;
	while (node != NULL)
	{
		tmp_redir = node->redir;
		while (tmp_redir != NULL)
		{
			if (tmp_redir->type == HEREDOC)
			{
				n = ft_itoa(num);
				new_filename = ft_strjoin("hrd_", n);
				num++;
				tmp_redir->filename = new_filename;
				free(n);
			}
			tmp_redir = tmp_redir->next;
		}
		node = node->next;
	}
	if (g_exit_code == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (SUCCESS);
}
