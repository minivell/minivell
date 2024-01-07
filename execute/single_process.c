#include "../minishell.h"

char	*get_cmd_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;
	char	*cmd_tmp;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	i = 0;
	cmd_path = ft_strjoin("/", cmd);
	while (path[i])
	{
		cmd_tmp = ft_strjoin(path[i], cmd_path);
		if (access(cmd_tmp, X_OK) == 0)
		{
			free(cmd_path);
			return (cmd_tmp);
		}
		free(cmd_tmp);
		i++;
	}
	free (cmd_path);
	return (NULL);
}


int	exec_cmd(char **cmd_arg, t_exec *exec_info)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(cmd_arg[0], exec_info->path);
	if (execve(cmd_path, cmd_arg, NULL) == -1)
		return (FAILURE);
	return (SUCCESS);
}

int	single_process(t_shell *shell_info, t_exec *exec_info)
{
	int	status;
	pid_t	pid;

	if (check_n_exec_builtin(shell_info->cmd) == SUCCESS)
		return (SUCCESS);
	else
	{
		pid = fork();
		if (pid < 0)
			return (FAILURE);
		else if (pid == 0)
			exec_cmd(shell_info->cmd->cmd_args, exec_info);
		wait(&status);
		return SUCCESS;
	}
}