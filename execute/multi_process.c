#include "../minishell.h"

void	wait_child(int last_child)
{
	int	status;
	int	i;

	i = 0;
	while (i < last_child)
	{
		wait(&status);
		i++;
	}
}

void	exec_parents_process(t_exec *exec_info)
{
	close(exec_info->pipe[O_STREAM]);
	if (dup2(exec_info->pipe[I_STREAM], STDIN_FILENO) == FAILURE)
		return ; // error
	close(exec_info->pipe[I_STREAM]);
}


void	exec_child_process(t_exec *exec_info, t_cmd *cmd, int order, int last_child)
{
	close(exec_info->pipe[I_STREAM]);
	if (order != last_child && dup2(exec_info->pipe[O_STREAM], STDOUT_FILENO) == FAILURE)
		return ; // error
	close(exec_info->pipe[O_STREAM]);

//	// for test {
//	t_redir *node;
//
//	node = (t_redir*)malloc(sizeof(t_redir));
//	if(node == NULL){
//		return ;
//	}
//	// }
//	set_for_redir(exec_info, cmd->redir);
	exec_cmd(cmd->cmd_args, exec_info);
}

void	multi_process(t_shell *shell_info, t_exec *exec_info)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		order;

	order = 1;
	cmd = shell_info->cmd;
	while (cmd)
	{
		if (pipe(exec_info->pipe) == FAILURE)
			return ; // error handle
		pid = fork();
		if (pid == FAILURE)
			return ;	// error handle
		else if (pid == SUCCESS)
			exec_child_process(exec_info, cmd, order, shell_info->pipe_cnt + 1);
		else
			exec_parents_process(exec_info);
		cmd = cmd->next;
		order++;
	}
	wait_child(shell_info->pipe_cnt + 1);
}