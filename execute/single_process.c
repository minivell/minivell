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
	if (cmd_tmp == NULL)
		exit (EXIT_FAILURE);
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd_tmp);
		if (cmd_path == NULL)
			exit (EXIT_FAILURE); // need to "command not found" error handle
		if (access(cmd_path, X_OK) == SUCCESS)
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
	if (execve(cmd_path, cmd_args, make_new_env(exec_info)) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}



void	single_process(t_shell *shell_info, t_exec *exec_info)
{
	int	status;
	pid_t	pid;

	if (shell_info->cmd->redir != NULL)
		set_for_redir(exec_info, shell_info->cmd->redir);
	if (check_n_exec_builtin(shell_info->cmd) == TRUE)
		return ;
	else
	{
		pid = fork();
		if (pid == FAILURE)
			return ;
		else if (pid == SUCCESS)
		{
			exec_cmd(shell_info->cmd->cmd_args, exec_info);
			exit (1);
		}
		wait(&status);
		return ;
	}
}