#include "../minishell.h"

int check_n_exec_builtin(t_cmd *cmd_info, t_exec *exec_info)
{
	char	*cmd;

	cmd = cmd_info->cmd_args[0];
	if (!cmd)
		return (FALSE);
	if (ft_strcmp(cmd, "echo") == 0)
	{
		printf("echo\n");
		g_exit_code = echo(cmd_info->cmd_args);
	}
	else if (ft_strcmp(cmd, "cd") == 0)
	{
		g_exit_code = cd(cmd_info->cmd_args, exec_info);
	}
	else if (ft_strcmp(cmd, "pwd") == 0)
	{
		g_exit_code = pwd();
	}
	else if (ft_strcmp(cmd, "export") == 0)
	{
		g_exit_code = export(exec_info, cmd_info->cmd_args);
	}
	else if (ft_strcmp(cmd, "unset") == 0)
	{
		g_exit_code = unset(exec_info, cmd_info->cmd_args);
	}
	else if (ft_strcmp(cmd, "env") == 0)
	{
		g_exit_code = env(exec_info);
	}
	else if (ft_strcmp(cmd, "exit") == 0)
	{
		g_exit_code = exit_shell();
	}
	else
		return (FALSE);
	return (TRUE);
}