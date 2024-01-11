#include "../minishell.h"

char	*get_cmd_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*cmd_tmp;

	if (cmd == NULL || path == NULL)
		return (NULL);
	i = 0;
	cmd_tmp = ft_strjoin("/", cmd);
	printf("cmd_tmp: %s\n", cmd_tmp);
	return (NULL);
	if (cmd_tmp == NULL)
		exit (EXIT_FAILURE);
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd_tmp);
		if (cmd_path == NULL)
			exit (EXIT_FAILURE); // need to "not found command" error handle
		if (access(cmd_path, X_OK) == 0)
		{
			free(cmd_tmp);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free (cmd_path);
	return (NULL);
}


int	exec_cmd(char **cmd_args, t_exec *exec_info)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd_args[0], exec_info->path);
	if (execve(cmd_path, cmd_args, NULL) < 0)
		return (FAILURE);
	return (SUCCESS);
}

void	set_for_redir(t_redir *redir)
{
	(void)redir;

	return ;
//	int	fd;
//	t_redir	*node;
//
//	node = redir;
//	while (node)
//	{
//		if (node->type == IN_REDIR)
//		{
//			fd = open(redir->file, O_RDONLY);
//			dup2(fd, STDIN_FILENO);
//			close(fd);
//		}
//		else if (redir->type == REDIR_OUT)
//		{
//			fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//			dup2(fd, STDOUT_FILENO);
//			close(fd);
//		}
//		else if (redir->type == REDIR_APPEND)
//		{
//			fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
//			dup2(fd, STDOUT_FILENO);
//			close(fd);
//		}
//		redir = redir->next;
//	}

}

void	single_process(t_shell *shell_info, t_exec *exec_info)
{
	int	status;
	pid_t	pid;

	if (shell_info->cmd->redir != NULL)
		set_for_redir(shell_info->cmd->redir);
	if (check_n_exec_builtin(shell_info->cmd) == TRUE)
		return ;
	else
	{
		pid = fork();
		if (pid < 0)
			return ;
		else if (pid == 0)
			exec_cmd(shell_info->cmd->cmd_args, exec_info);
		wait(&status);
		return ;
	}
}